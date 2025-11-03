#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define NUM_READERS 5
#define NUM_WRITERS 2
#define NUM_OPERATIONS 3

// Recurso compartido (base de datos simulada)
int shared_data = 0;
int readers_count = 0;

// Semáforos y mutex
sem_t rw_mutex;        // Semáforo para escritores y primer/último lector
pthread_mutex_t read_count_mutex; // Mutex para proteger readers_count

// Función del lector
void* reader(void* arg) {
    int reader_id = *(int*)arg;
    
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        // Protocolo de entrada del lector
        pthread_mutex_lock(&read_count_mutex);
        readers_count++;
        if (readers_count == 1) {
            // Primer lector bloquea a escritores
            sem_wait(&rw_mutex);
        }
        pthread_mutex_unlock(&read_count_mutex);
        
        // === SECCIÓN CRÍTICA DE LECTURA ===
        printf("Lector %d está leyendo... Dato: %d (Operación %d)\n", 
               reader_id, shared_data, i + 1);
        fflush(stdout);
        
        // Simular tiempo de lectura
        usleep(rand() % 300000 + 100000); // 100-400ms
        
        printf("Lector %d terminó de leer (Operación %d)\n", 
               reader_id, i + 1);
        fflush(stdout);
        // === FIN SECCIÓN CRÍTICA DE LECTURA ===
        
        // Protocolo de salida del lector
        pthread_mutex_lock(&read_count_mutex);
        readers_count--;
        if (readers_count == 0) {
            // Último lector permite a escritores
            sem_post(&rw_mutex);
        }
        pthread_mutex_unlock(&read_count_mutex);
        
        // Pausa entre operaciones
        usleep(rand() % 500000);
    }
    
    printf("🔍 Lector %d TERMINÓ todas sus operaciones\n", reader_id);
    return NULL;
}

// Función del escritor
void* writer(void* arg) {
    int writer_id = *(int*)arg;
    
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        // Protocolo de entrada del escritor
        sem_wait(&rw_mutex); // Esperar acceso exclusivo
        
        // === SECCIÓN CRÍTICA DE ESCRITURA ===
        int old_value = shared_data;
        shared_data = writer_id * 1000 + i + 1;
        
        printf("✏️  Escritor %d está escribiendo... Cambió %d → %d (Operación %d)\n", 
               writer_id, old_value, shared_data, i + 1);
        fflush(stdout);
        
        // Simular tiempo de escritura
        usleep(rand() % 400000 + 200000); // 200-600ms
        
        printf("✏️  Escritor %d terminó de escribir (Operación %d)\n", 
               writer_id, i + 1);
        fflush(stdout);
        // === FIN SECCIÓN CRÍTICA DE ESCRITURA ===
        
        // Protocolo de salida del escritor
        sem_post(&rw_mutex); // Liberar acceso
        
        // Pausa entre operaciones
        usleep(rand() % 600000);
    }
    
    printf("📝 Escritor %d TERMINÓ todas sus operaciones\n", writer_id);
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];
    
    // Inicializar semilla para números aleatorios
    srand(time(NULL));
    
    // Inicializar semáforos y mutex
    sem_init(&rw_mutex, 0, 1);           // Inicialmente disponible
    pthread_mutex_init(&read_count_mutex, NULL);
    
    printf("=== Problema Lector-Escritor ===\n");
    printf("Lectores: %d, Escritores: %d\n", NUM_READERS, NUM_WRITERS);
    printf("Operaciones por hilo: %d\n", NUM_OPERATIONS);
    printf("Dato inicial: %d\n\n", shared_data);
    
    // Crear hilos lectores
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        if (pthread_create(&readers[i], NULL, reader, &reader_ids[i]) != 0) {
            perror("Error creando hilo lector");
            exit(1);
        }
    }
    
    // Crear hilos escritores
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        if (pthread_create(&writers[i], NULL, writer, &writer_ids[i]) != 0) {
            perror("Error creando hilo escritor");
            exit(1);
        }
    }
    
    // Esperar a que terminen todos los lectores
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    
    // Esperar a que terminen todos los escritores
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }
    
    printf("\n=== Todos los hilos terminaron ===\n");
    printf("Valor final del dato compartido: %d\n", shared_data);
    
    // Limpiar recursos
    sem_destroy(&rw_mutex);
    pthread_mutex_destroy(&read_count_mutex);
    
    return 0;
}