/*
6. Suma paralela con memoria compartida
Objetivo: Dividir el trabajo entre procesos e integrar los resultados usando memoria compartida.
Resuelva:
El padre crea un arreglo de enteros en memoria compartida.
Crea N procesos que suman distintas partes del arreglo (por ejemplo de a pares).
Cada hijo indica que parte sumó y el resultado.
Extensión: Cada proceso guarda la suma parcial en un arreglo auxiliar (compartido) y el padre
calcula la suma total del arreglo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h> // Agrega esta línea
#include <unistd.h>

void check_error(int result, const char* msg) {
    if(result < 0) {
        perror(msg);
        exit(EXIT_FAILURE);
    }
}

int main(){
    int key = ftok(".", 'C'); // Cambia "C" por 'C'
    
    int TAM = 10; // Tamaño del arreglo
    int N = 2;    // Cantidad de procesos hijos 
    
    int shmid = shmget(key, sizeof(int) * TAM, IPC_CREAT | 0666); //Segmento de memoria compartida para el arreglo
    int shmid_resultados = shmget(key + 1, sizeof(int) * N, IPC_CREAT | 0666); //Segmento de memoria compartida para los resultados
    int *arreglo;
    int *resultados;
    pid_t pid;
    int suma_total = 0;

    //Chequeo de errores
    check_error(key, "Error en ftok");
    check_error(shmid, "Error en shmget");
    check_error(shmid_resultados, "Error en shmget resultados");

    arreglo = shmat(shmid, NULL, 0); //Adjunta el segmento de memoria compartida
    resultados = shmat(shmid_resultados, NULL, 0); //Adjunta el segmento de memoria compartida para los resultados

    // Inicializamos directamente el arreglo en memoria compartida
    for(int i = 0; i < TAM; i++) {
        arreglo[i] = i + 1; // Esto genera el arreglo {1,2,3,4,5,6,7,8,9,10}
    }

    // Crear N procesos hijos
    for(int i = 0; i < N; i++) {
        pid = fork();
        if(pid == 0) {
            // Cada hijo suma 5 elementos
            int inicio = i * 5;
            int fin = inicio + 5;
            int suma = 0;
            for(int j = inicio; j < fin; j++) {
                suma += arreglo[j];
            }
            resultados[i] = suma;
            printf("Hijo %d: sumé arreglo[%d] a arreglo[%d] = %d\n", i+1, inicio, fin-1, suma);
            shmdt(arreglo);
            shmdt(resultados);
            exit(0);
        }
    }

    // Esperar a que todos los hijos terminen
    for(int i = 0; i < N; i++) {
        wait(NULL);
    }

    // El padre suma los resultados parciales
    for(int i = 0; i < N; i++) {
        suma_total += resultados[i];
    }
    printf("Suma total del arreglo: %d\n", suma_total);

    // Liberar memoria compartida
    shmdt(arreglo);
    shmdt(resultados);
    shmctl(shmid, IPC_RMID, NULL);
    shmctl(shmid_resultados, IPC_RMID, NULL);

    return 0;
}