#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <time.h>

#define NUM_PHILOSOPHERS 5
#define NUM_MEALS 3

typedef enum {
    THINKING,
    HUNGRY,
    EATING
} philosopher_state_t;

// Estructura para datos compartidos
typedef struct {
    philosopher_state_t state[NUM_PHILOSOPHERS];
    int meals_eaten[NUM_PHILOSOPHERS];
    sem_t mutex;
    sem_t philosophers[NUM_PHILOSOPHERS];
} shared_data_t;

int left_neighbor(int philosopher_id) {
    return (philosopher_id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS;
}

int right_neighbor(int philosopher_id) {
    return (philosopher_id + 1) % NUM_PHILOSOPHERS;
}

void test_philosopher(shared_data_t *shared, int philosopher_id) {
    int left = left_neighbor(philosopher_id);
    int right = right_neighbor(philosopher_id);
    
    if (shared->state[philosopher_id] == HUNGRY && 
        shared->state[left] != EATING && 
        shared->state[right] != EATING) {
        
        shared->state[philosopher_id] = EATING;
        printf("🍽️  Filósofo %d (PID: %d) está COMIENDO (comida %d/%d)\n", 
               philosopher_id, getpid(), shared->meals_eaten[philosopher_id] + 1, NUM_MEALS);
        fflush(stdout);
        
        sem_post(&shared->philosophers[philosopher_id]);
    }
}

void pickup_forks(shared_data_t *shared, int philosopher_id) {
    sem_wait(&shared->mutex);
    
    shared->state[philosopher_id] = HUNGRY;
    printf("🍴 Filósofo %d (PID: %d) está HAMBRIENTO\n", philosopher_id, getpid());
    fflush(stdout);
    
    test_philosopher(shared, philosopher_id);
    
    sem_post(&shared->mutex);
    sem_wait(&shared->philosophers[philosopher_id]);
}

void putdown_forks(shared_data_t *shared, int philosopher_id) {
    sem_wait(&shared->mutex);
    
    shared->state[philosopher_id] = THINKING;
    printf("🤔 Filósofo %d (PID: %d) está PENSANDO\n", philosopher_id, getpid());
    fflush(stdout);
    
    test_philosopher(shared, left_neighbor(philosopher_id));
    test_philosopher(shared, right_neighbor(philosopher_id));
    
    sem_post(&shared->mutex);
}

void philosopher_process(shared_data_t *shared, int philosopher_id) {
    printf("🧠 Filósofo %d (PID: %d) se sentó a la mesa\n", philosopher_id, getpid());
    fflush(stdout);
    
    for (int meal = 0; meal < NUM_MEALS; meal++) {
        // Pensar
        printf("🤔 Filósofo %d (PID: %d) está pensando...\n", philosopher_id, getpid());
        fflush(stdout);
        usleep(rand() % 2000000 + 500000);
        
        // Intentar comer
        pickup_forks(shared, philosopher_id);
        
        // Comer
        shared->meals_eaten[philosopher_id]++;
        usleep(rand() % 1500000 + 500000);
        
        printf("✅ Filósofo %d (PID: %d) terminó de comer (comida %d/%d)\n", 
               philosopher_id, getpid(), shared->meals_eaten[philosopher_id], NUM_MEALS);
        fflush(stdout);
        
        // Soltar tenedores
        putdown_forks(shared, philosopher_id);
        
        usleep(rand() % 500000);
    }
    
    printf("🎉 Filósofo %d (PID: %d) TERMINÓ todas sus comidas (%d/%d)\n", 
           philosopher_id, getpid(), shared->meals_eaten[philosopher_id], NUM_MEALS);
    fflush(stdout);
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
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        shared->state[i] = THINKING;
        shared->meals_eaten[i] = 0;
    }
    
    // Inicializar semáforos
    sem_init(&shared->mutex, 1, 1);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&shared->philosophers[i], 1, 0);
    }
    
    srand(time(NULL));
    
    printf("=== Filósofos Comensales con PROCESOS ===\n");
    printf("Número de filósofos: %d\n", NUM_PHILOSOPHERS);
    printf("Comidas por filósofo: %d\n", NUM_MEALS);
    printf("========================================\n\n");
    
    // Crear procesos filósofos
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            philosopher_process(shared, i);
            exit(0);
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        }
    }
    
    // Esperar a todos los procesos hijos
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        wait(NULL);
    }
    
    printf("\n=== Todos los procesos terminaron ===\n");
    
    int total_meals = 0;
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        total_meals += shared->meals_eaten[i];
    }
    printf("Total de comidas servidas: %d/%d\n", total_meals, NUM_PHILOSOPHERS * NUM_MEALS);
    
    // Limpiar recursos
    sem_destroy(&shared->mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&shared->philosophers[i]);
    }
    munmap(shared, sizeof(shared_data_t));
    
    return 0;
}