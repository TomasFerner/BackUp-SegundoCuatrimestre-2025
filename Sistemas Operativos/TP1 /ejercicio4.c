#include <stdio.h>
#include <pthread.h>

#define M 5 // Número de hilos

void* hilo_func(void* arg) {
    int id = *(int*)arg;
    printf("Hola, soy el hilo %d\n", id);
    return NULL;
}

int main() {
    pthread_t hilos[M];
    int ids[M];

    // Crear M hilos
    for (int i = 0; i < M; i++) {
        ids[i] = i + 1;
        if (pthread_create(&hilos[i], NULL, hilo_func, &ids[i]) != 0) {
            perror("Error al crear hilo");
            return 1;
        }
    }

    // Esperar la finalización de todos los hilos
    for (int i = 0; i < M; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("Todos los hilos han terminado.\n");
    return 0;
}