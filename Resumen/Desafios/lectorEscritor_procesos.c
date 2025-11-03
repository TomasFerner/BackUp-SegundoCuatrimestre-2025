#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <time.h>

#define NUM_READERS 5
#define NUM_WRITERS 2
#define NUM_OPERATIONS 3

// Estructura para datos compartidos
typedef struct {
    int shared_data;
    int readers_count;
    sem_t rw_mutex;
    sem_t read_count_mutex;
} shared_data_t;

void reader_process(shared_data_t *shared, int reader_id) {
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        // Protocolo de entrada del lector
        sem_wait(&shared->read_count_mutex);
        shared->readers_count++;
        if (shared->readers_count == 1) {
            sem_wait(&shared->rw_mutex);
        }
        sem_post(&shared->read_count_mutex);
        
        // Sección crítica de lectura
        printf("Lector %d (PID: %d) está leyendo... Dato: %d (Operación %d)\n", 
               reader_id, getpid(), shared->shared_data, i + 1);
        fflush(stdout);
        
        usleep(rand() % 300000 + 100000);
        
        printf("Lector %d (PID: %d) terminó de leer (Operación %d)\n", 
               reader_id, getpid(), i + 1);
        fflush(stdout);
        
        // Protocolo de salida del lector
        sem_wait(&shared->read_count_mutex);
        shared->readers_count--;
        if (shared->readers_count == 0) {
            sem_post(&shared->rw_mutex);
        }
        sem_post(&shared->read_count_mutex);
        
        usleep(rand() % 500000);
    }
    
    printf("🔍 Lector %d (PID: %d) TERMINÓ todas sus operaciones\n", reader_id, getpid());
}

void writer_process(shared_data_t *shared, int writer_id) {
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        // Protocolo de entrada del escritor
        sem_wait(&shared->rw_mutex);
        
        // Sección crítica de escritura
        int old_value = shared->shared_data;
        shared->shared_data = writer_id * 1000 + i + 1;
        
        printf("✏️  Escritor %d (PID: %d) escribió... Cambió %d → %d (Operación %d)\n", 
               writer_id, getpid(), old_value, shared->shared_data, i + 1);
        fflush(stdout);
        
        usleep(rand() % 400000 + 200000);
        
        printf("✏️  Escritor %d (PID: %d) terminó de escribir (Operación %d)\n", 
               writer_id, getpid(), i + 1);
        fflush(stdout);
        
        // Protocolo de salida del escritor
        sem_post(&shared->rw_mutex);
        
        usleep(rand() % 600000);
    }
    
    printf("📝 Escritor %d (PID: %d) TERMINÓ todas sus operaciones\n", writer_id, getpid());
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
    shared->shared_data = 0;
    shared->readers_count = 0;
    
    // Inicializar semáforos
    sem_init(&shared->rw_mutex, 1, 1);
    sem_init(&shared->read_count_mutex, 1, 1);
    
    srand(time(NULL));
    
    printf("=== Lector-Escritor con PROCESOS ===\n");
    printf("Lectores: %d, Escritores: %d\n", NUM_READERS, NUM_WRITERS);
    printf("Dato inicial: %d\n\n", shared->shared_data);
    
    // Crear procesos lectores
    for (int i = 0; i < NUM_READERS; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            reader_process(shared, i + 1);
            exit(0);
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        }
    }
    
    // Crear procesos escritores
    for (int i = 0; i < NUM_WRITERS; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            writer_process(shared, i + 1);
            exit(0);
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        }
    }
    
    // Esperar a todos los procesos hijos
    for (int i = 0; i < NUM_READERS + NUM_WRITERS; i++) {
        wait(NULL);
    }
    
    printf("\n=== Todos los procesos terminaron ===\n");
    printf("Valor final del dato compartido: %d\n", shared->shared_data);
    
    // Limpiar recursos
    sem_destroy(&shared->rw_mutex);
    sem_destroy(&shared->read_count_mutex);
    munmap(shared, sizeof(shared_data_t));
    
    return 0;
}