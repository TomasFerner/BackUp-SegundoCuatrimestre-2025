#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>

#define MAX_PASAJEROS 5
#define NUM_PASAJEROS 7

// Semáforos
sem_t asientos_disponibles;  // Contador de asientos (capacidad del colectivo)
sem_t colectivo_lleno;       // Señal para que el colectivo parta
sem_t mutex_salida;          // Mutex para controlar la salida del colectivo

void* pasajero(void* arg) {
    int id = *(int*)arg;
    
    printf("Pasajero %d llegó a la parada\n", id);
    
    // Intentar subir al colectivo
    if (sem_trywait(&asientos_disponibles) == 0) {
        printf("Pasajero %d subió al colectivo\n", id);
        
        // Verificar si el colectivo está lleno
        int asientos_restantes;
        sem_getvalue(&asientos_disponibles, &asientos_restantes);
        
        if (asientos_restantes == 0) {
            printf("Pasajero %d fue el último en subir. El colectivo está lleno!\n", id);
            sem_post(&colectivo_lleno);  // Señalar que el colectivo puede partir
        }
        
        // Esperar a que el colectivo parta
        sem_wait(&mutex_salida);
        printf("Pasajero %d viajando en el colectivo\n", id);
        sleep(2);  // Simular viaje
        printf("Pasajero %d bajó del colectivo\n", id);
        sem_post(&mutex_salida);
        
    } else {
        printf("Pasajero %d no pudo subir - colectivo lleno\n", id);
    }
    
    free(arg);
    return NULL;
}

void* conductor(void* arg) {
    printf("Conductor esperando que se llene el colectivo...\n");
    
    // Esperar a que el colectivo se llene
    sem_wait(&colectivo_lleno);
    
    printf("¡CONDUCTOR: El colectivo está lleno! Partiendo...\n");
    sleep(1);  // Simular arranque
    
    // Permitir que los pasajeros "viajen"
    for (int i = 0; i < MAX_PASAJEROS; i++) {
        sem_post(&mutex_salida);
    }
    
    sleep(3);  // Simular duración del viaje
    
    printf("CONDUCTOR: Llegamos al destino\n");
    
    // Reiniciar asientos para el próximo viaje
    for (int i = 0; i < MAX_PASAJEROS; i++) {
        sem_post(&asientos_disponibles);
        sem_wait(&mutex_salida);
    }
    
    return NULL;
}

int main() {
    pthread_t hilos_pasajeros[NUM_PASAJEROS];
    pthread_t hilo_conductor;
    
    // Inicializar semáforos
    sem_init(&asientos_disponibles, 0, MAX_PASAJEROS);  // 5 asientos disponibles
    sem_init(&colectivo_lleno, 0, 0);                   // Inicialmente no está lleno
    sem_init(&mutex_salida, 0, 0);                      // Inicialmente bloqueado
    
    printf("=== SIMULACIÓN COLECTIVO ===\n");
    printf("Capacidad: %d pasajeros\n", MAX_PASAJEROS);
    printf("Pasajeros esperando: %d\n\n", NUM_PASAJEROS);
    
    // Crear hilo conductor
    pthread_create(&hilo_conductor, NULL, conductor, NULL);
    
    // Crear hilos pasajeros
    for (int i = 0; i < NUM_PASAJEROS; i++) {
        int* id = malloc(sizeof(int));//Reservar memoria para el ID del pasajero
        *id = i + 1;
        pthread_create(&hilos_pasajeros[i], NULL, pasajero, id);
        usleep(100000);  // Pequeña pausa entre llegadas
    }
    
    // Esperar a que terminen todos los hilos
    for (int i = 0; i < NUM_PASAJEROS; i++) {
        pthread_join(hilos_pasajeros[i], NULL);
    }
    pthread_join(hilo_conductor, NULL);
    
    // Limpiar semáforos
    sem_destroy(&asientos_disponibles);
    sem_destroy(&colectivo_lleno);
    sem_destroy(&mutex_salida);
    
    printf("\n=== SIMULACIÓN TERMINADA ===\n");
    return 0;
}