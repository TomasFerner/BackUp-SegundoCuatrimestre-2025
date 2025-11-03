#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <time.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define NUM_ITEMS 10

// Estructura para datos compartidos
typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    sem_t empty;
    sem_t full;
    sem_t mutex;
} shared_data_t;

void producer_process(shared_data_t *shared, int producer_id) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = producer_id * 100 + i;
        
        sem_wait(&shared->empty);
        sem_wait(&shared->mutex);
        
        shared->buffer[shared->in] = item;
        printf("Productor %d (PID: %d) produjo item %d en posición %d\n", 
               producer_id, getpid(), item, shared->in);
        fflush(stdout);
        shared->in = (shared->in + 1) % BUFFER_SIZE;
        
        sem_post(&shared->mutex);
        sem_post(&shared->full);
        
        usleep(rand() % 500000);
    }
    printf("Productor %d (PID: %d) terminó\n", producer_id, getpid());
}

void consumer_process(shared_data_t *shared, int consumer_id) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&shared->full);
        sem_wait(&shared->mutex);
        
        int item = shared->buffer[shared->out];
        printf("Consumidor %d (PID: %d) consumió item %d de posición %d\n", 
               consumer_id, getpid(), item, shared->out);
        fflush(stdout);
        shared->out = (shared->out + 1) % BUFFER_SIZE;
        
        sem_post(&shared->mutex);
        sem_post(&shared->empty);
        
        usleep(rand() % 700000);
    }
    printf("Consumidor %d (PID: %d) terminó\n", consumer_id, getpid());
}

int main() {
    // Crear memoria compartida
    shared_data_t *shared = mmap(NULL, sizeof(shared_data_t), 
                                PROT_READ | PROT_WRITE, 
                                MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
    if (shared == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    
    // Inicializar datos compartidos
    shared->in = 0;
    shared->out = 0;
    
    // Inicializar semáforos (compartidos entre procesos)
    sem_init(&shared->empty, 1, BUFFER_SIZE);
    sem_init(&shared->full, 1, 0);
    sem_init(&shared->mutex, 1, 1);
    
    srand(time(NULL));
    
    printf("=== Productor-Consumidor con PROCESOS ===\n");
    printf("Buffer size: %d, Productores: %d, Consumidores: %d\n\n", 
           BUFFER_SIZE, NUM_PRODUCERS, NUM_CONSUMERS);
    
    // Crear procesos productores
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            producer_process(shared, i + 1);
            exit(0);
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        }
    }
    
    // Crear procesos consumidores
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            consumer_process(shared, i + 1);
            exit(0);
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        }
    }
    
    // Esperar a todos los procesos hijos
    for (int i = 0; i < NUM_PRODUCERS + NUM_CONSUMERS; i++) {
        wait(NULL);
    }
    
    printf("\n=== Todos los procesos terminaron ===\n");
    
    // Limpiar recursos
    sem_destroy(&shared->empty);
    sem_destroy(&shared->full);
    sem_destroy(&shared->mutex);
    munmap(shared, sizeof(shared_data_t));
    
    return 0;
}