#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define NUM_ITEMS 10

// Buffer compartido
int buffer[BUFFER_SIZE];
int in = 0;  // Índice para insertar
int out = 0; // Índice para extraer

// Semáforos
sem_t empty;  // Espacios vacíos en el buffer
sem_t full;   // Elementos en el buffer
pthread_mutex_t mutex; // Mutex para acceso exclusivo al buffer

// Función del productor
void* producer(void* arg) {
    int producer_id = *(int*)arg;
    
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = producer_id * 100 + i; // Crear item único
        
        // Esperar espacio vacío
        sem_wait(&empty);
        
        // Entrar a sección crítica
        pthread_mutex_lock(&mutex);
        
        // Producir item
        buffer[in] = item;
        printf("Productor %d produjo item %d en posición %d\n", 
               producer_id, item, in);
        fflush(stdout);
        in = (in + 1) % BUFFER_SIZE;
        
        // Salir de sección crítica
        pthread_mutex_unlock(&mutex);
        
        // Señalar que hay un nuevo item
        sem_post(&full);
        
        // Simular tiempo de producción
        usleep(rand() % 500000);
    }
    
    printf("Productor %d terminó\n", producer_id);
    return NULL;
}

// Función del consumidor
void* consumer(void* arg) {
    int consumer_id = *(int*)arg;
    
    for (int i = 0; i < NUM_ITEMS; i++) {
        // Esperar item disponible
        sem_wait(&full);
        
        // Entrar a sección crítica
        pthread_mutex_lock(&mutex);
        
        // Consumir item
        int item = buffer[out];
        printf("Consumidor %d consumió item %d de posición %d\n", 
               consumer_id, item, out);
        fflush(stdout);
        out = (out + 1) % BUFFER_SIZE;
        
        // Salir de sección crítica
        pthread_mutex_unlock(&mutex);
        
        // Señalar que hay un espacio vacío
        sem_post(&empty);
        
        // Simular tiempo de consumo
        usleep(rand() % 700000);
    }
    
    printf("Consumidor %d terminó\n", consumer_id);
    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];
    int producer_ids[NUM_PRODUCERS];
    int consumer_ids[NUM_CONSUMERS];
    
    // Inicializar semilla para números aleatorios
    srand(time(NULL));
    
    // Inicializar semáforos y mutex
    sem_init(&empty, 0, BUFFER_SIZE); // Buffer inicialmente vacío
    sem_init(&full, 0, 0);            // Sin items inicialmente
    pthread_mutex_init(&mutex, NULL);
    
    printf("=== Problema Productor-Consumidor ===\n");
    printf("Buffer size: %d\n", BUFFER_SIZE);
    printf("Productores: %d, Consumidores: %d\n", NUM_PRODUCERS, NUM_CONSUMERS);
    printf("Items por hilo: %d\n\n", NUM_ITEMS);
    
    // Crear hilos productores
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        producer_ids[i] = i + 1;
        if (pthread_create(&producers[i], NULL, producer, &producer_ids[i]) != 0) {
            perror("Error creando hilo productor");
            exit(1);
        }
    }
    
    // Crear hilos consumidores
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        consumer_ids[i] = i + 1;
        if (pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]) != 0) {
            perror("Error creando hilo consumidor");
            exit(1);
        }
    }
    
    // Esperar a que terminen todos los productores
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }
    
    // Esperar a que terminen todos los consumidores
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }
    
    printf("\n=== Todos los hilos terminaron ===\n");
    
    // Limpiar recursos
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}