#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define N 4           // Cantidad de procesos hijos
#define ARR_SIZE 8    // Tamaño del arreglo a sumar

int main() {
    key_t key_arr, key_sumas;
    int shmid_arr, shmid_sumas;
    int *arr, *sumas;
    pid_t pid;

    // Crear clave y segmento de memoria compartida para el arreglo
    key_arr = ftok(".", 'D');
    if (key_arr == -1) { perror("ftok arr"); exit(EXIT_FAILURE); }
    shmid_arr = shmget(key_arr, ARR_SIZE * sizeof(int), IPC_CREAT | 0666);
    if (shmid_arr == -1) { perror("shmget arr"); exit(EXIT_FAILURE); }

    // Crear clave y segmento de memoria compartida para las sumas parciales
    key_sumas = ftok(".", 'E');
    if (key_sumas == -1) { perror("ftok sumas"); shmctl(shmid_arr, IPC_RMID, NULL); exit(EXIT_FAILURE); }
    shmid_sumas = shmget(key_sumas, N * sizeof(int), IPC_CREAT | 0666);
    if (shmid_sumas == -1) { perror("shmget sumas"); shmctl(shmid_arr, IPC_RMID, NULL); exit(EXIT_FAILURE); }

    // Adjuntar los segmentos
    arr = (int *)shmat(shmid_arr, NULL, 0);
    sumas = (int *)shmat(shmid_sumas, NULL, 0);
    if (arr == (void *)-1 || sumas == (void *)-1) {
        perror("shmat");
        shmctl(shmid_arr, IPC_RMID, NULL);
        shmctl(shmid_sumas, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }

    // Inicializar el arreglo y sumas parciales
    for (int i = 0; i < ARR_SIZE; i++) arr[i] = i + 1; // {1,2,3,4,5,6,7,8}
    for (int i = 0; i < N; i++) sumas[i] = 0;

    // Crear N procesos hijos
    int elems_por_hijo = ARR_SIZE / N;
    for (int i = 0; i < N; i++) {
        pid = fork();
        if (pid == 0) {
            int inicio = i * elems_por_hijo;
            int fin = (i == N-1) ? ARR_SIZE : inicio + elems_por_hijo; // Último hijo suma el resto
            int suma = 0;
            for (int j = inicio; j < fin; j++) suma += arr[j];
            sumas[i] = suma;
            printf("Hijo %d sumó arr[%d..%d) = %d\n", i, inicio, fin, suma);
            shmdt(arr);
            shmdt(sumas);
            exit(0);
        }
    }

    // Esperar a los hijos
    for (int i = 0; i < N; i++) wait(NULL);

    // El padre calcula la suma total
    int suma_total = 0;
    for (int i = 0; i < N; i++) suma_total += sumas[i];
    printf("Suma total del arreglo: %d\n", suma_total);

    // Liberar memoria compartida
    shmdt(arr);
    shmdt(sumas);
    shmctl(shmid_arr, IPC_RMID, NULL);
    shmctl(shmid_sumas, IPC_RMID, NULL);

    return 0;
}