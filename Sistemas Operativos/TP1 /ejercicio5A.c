#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <unistd.h>

#define N 8
#define NUM_PROC 2

int main() {
    int arr[N] = {1,2,3,4,5,6,7,8};

    // Crear un segmento de memoria compartida para guardar las sumas parciales de cada proceso
    int shmid = shmget(IPC_PRIVATE, sizeof(int)*NUM_PROC, IPC_CREAT | 0666);

    // Asociar el segmento de memoria compartida al espacio de direcciones del proceso
    int *suma_parcial = (int*)shmat(shmid, NULL, 0);

    // Crear procesos hijos para calcular sumas parciales
    for (int i = 0; i < NUM_PROC; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Cada hijo calcula la suma de una parte del arreglo
            int suma = 0;
            for (int j = i*(N/NUM_PROC); j < (i+1)*(N/NUM_PROC); j++)
                suma += arr[j];
            // Guarda la suma parcial en la memoria compartida
            suma_parcial[i] = suma;
            // Desasocia la memoria compartida antes de salir
            shmdt(suma_parcial);
            exit(0);
        }
    }

    // El proceso padre espera a que todos los hijos terminen
    for (int i = 0; i < NUM_PROC; i++)
        wait(NULL);

    // El padre suma las sumas parciales de los hijos
    int total = 0;
    for (int i = 0; i < NUM_PROC; i++)
        total += suma_parcial[i];

    printf("Suma total (procesos): %d\n", total);

    // Desasocia y elimina el segmento de memoria compartida
    shmdt(suma_parcial);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}