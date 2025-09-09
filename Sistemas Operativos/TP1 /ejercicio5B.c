#include <stdio.h>
#include <pthread.h>

#define N 8
#define NUM_HILOS 2

int arr[N] = {1,2,3,4,5,6,7,8};
int suma_parcial[NUM_HILOS];

// Función que ejecuta cada hilo para sumar una parte del arreglo
void* sumar(void* arg) {
    int id = *(int*)arg;
    suma_parcial[id] = 0;
    // Cada hilo suma una parte del arreglo
    for (int i = id*(N/NUM_HILOS); i < (id+1)*(N/NUM_HILOS); i++)
        suma_parcial[id] += arr[i];
    return NULL;
}

int main() {
    pthread_t hilos[NUM_HILOS];
    int ids[NUM_HILOS];

    // Crear los hilos y asignarles su identificador
    for (int i = 0; i < NUM_HILOS; i++) {
        ids[i] = i;
        pthread_create(&hilos[i], NULL, sumar, &ids[i]);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_HILOS; i++)
        pthread_join(hilos[i], NULL);

    // Sumar los resultados parciales de cada hilo
    int total = 0;
    for (int i = 0; i < NUM_HILOS; i++)
        total += suma_parcial[i];

    printf("Suma total (hilos): %d\n", total);
    return 0;
}