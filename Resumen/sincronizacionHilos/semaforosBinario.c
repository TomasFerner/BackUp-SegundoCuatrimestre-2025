#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Semáforos binarios para sincronización
sem_t sem_A, sem_B, sem_C;

// Contador global para limitar las iteraciones
int contador_global = 0;
int MAX_ITERACIONES = 9; // Para imprimir ABCABCABC (9 caracteres)

void* hilo_A(void* arg) {
    while (contador_global < MAX_ITERACIONES) {
        // Esperar turno para A
        sem_wait(&sem_A);
        
        if (contador_global < MAX_ITERACIONES) {
            printf("A");
            fflush(stdout);
            contador_global++;
            
            // Simular tiempo de procesamiento
            usleep(100000); // 0.1 segundos
            
            // Dar turno a B
            sem_post(&sem_B);
        } else {
            // Si ya terminamos, liberar para que otros hilos puedan terminar
            sem_post(&sem_B);
            break;
        }
    }
    return NULL;
}

void* hilo_B(void* arg) {
    while (contador_global < MAX_ITERACIONES) {
        // Esperar turno para B
        sem_wait(&sem_B);
        
        if (contador_global < MAX_ITERACIONES) {
            printf("B");
            fflush(stdout);
            contador_global++;
            
            // Simular tiempo de procesamiento
            usleep(100000); // 0.1 segundos
            
            // Dar turno a C
            sem_post(&sem_C);
        } else {
            // Si ya terminamos, liberar para que otros hilos puedan terminar
            sem_post(&sem_C);
            break;
        }
    }
    return NULL;
}

void* hilo_C(void* arg) {
    while (contador_global < MAX_ITERACIONES) {
        // Esperar turno para C
        sem_wait(&sem_C);
        
        if (contador_global < MAX_ITERACIONES) {
            printf("C");
            fflush(stdout);
            contador_global++;
            
            // Simular tiempo de procesamiento
            usleep(100000); // 0.1 segundos
            
            // Dar turno a A (completar el ciclo)
            sem_post(&sem_A);
        } else {
            // Si ya terminamos, liberar para que otros hilos puedan terminar
            sem_post(&sem_A);
            break;
        }
    }
    return NULL;
}

int main() {
    pthread_t hilos[3];
    
    printf("Iniciando secuencia ABC con semáforos:\n");
    
    // Inicializar semáforos binarios
    // sem_A comienza en 1 (disponible), otros en 0 (bloqueados)
    if (sem_init(&sem_A, 0, 1) != 0) {
        perror("Error inicializando sem_A");
        exit(1);
    }
    if (sem_init(&sem_B, 0, 0) != 0) {
        perror("Error inicializando sem_B");
        exit(1);
    }
    if (sem_init(&sem_C, 0, 0) != 0) {
        perror("Error inicializando sem_C");
        exit(1);
    }
    
    // Crear hilos
    if (pthread_create(&hilos[0], NULL, hilo_A, NULL) != 0) {
        perror("Error creando hilo A");
        exit(1);
    }
    if (pthread_create(&hilos[1], NULL, hilo_B, NULL) != 0) {
        perror("Error creando hilo B");
        exit(1);
    }
    if (pthread_create(&hilos[2], NULL, hilo_C, NULL) != 0) {
        perror("Error creando hilo C");
        exit(1);
    }
    
    // Esperar a que todos los hilos terminen
    for (int i = 0; i < 3; i++) {
        if (pthread_join(hilos[i], NULL) != 0) {
            perror("Error esperando hilo");
            exit(1);
        }
    }
    
    printf("\nSecuencia completada!\n");
    printf("Total de caracteres impresos: %d\n", contador_global);
    
    // Destruir semáforos
    sem_destroy(&sem_A);
    sem_destroy(&sem_B);
    sem_destroy(&sem_C);
    
    return 0;
}