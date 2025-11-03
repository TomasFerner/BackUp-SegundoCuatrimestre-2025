#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define NUM_PHILOSOPHERS 5
#define NUM_MEALS 3

// Estados de los filósofos
typedef enum {
    THINKING,
    HUNGRY,
    EATING
} philosopher_state_t;

// Variables globales
philosopher_state_t state[NUM_PHILOSOPHERS];
sem_t mutex;                          // Mutex para acceso a estados
sem_t philosophers[NUM_PHILOSOPHERS]; // Semáforo por filósofo
int meals_eaten[NUM_PHILOSOPHERS];    // Contador de comidas por filósofo

// Función para obtener el filósofo de la izquierda
int left_neighbor(int philosopher_id) {
    return (philosopher_id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS;
}

// Función para obtener el filósofo de la derecha
int right_neighbor(int philosopher_id) {
    return (philosopher_id + 1) % NUM_PHILOSOPHERS;
}

// Función para verificar si un filósofo puede comer
void test_philosopher(int philosopher_id) {
    int left = left_neighbor(philosopher_id);
    int right = right_neighbor(philosopher_id);
    
    // Un filósofo puede comer si está hambriento y sus vecinos no están comiendo
    if (state[philosopher_id] == HUNGRY && 
        state[left] != EATING && 
        state[right] != EATING) {
        
        state[philosopher_id] = EATING;
        printf("🍽️  Filósofo %d está COMIENDO (comida %d/%d)\n", 
               philosopher_id, meals_eaten[philosopher_id] + 1, NUM_MEALS);
        fflush(stdout);
        
        // Permitir al filósofo comer
        sem_post(&philosophers[philosopher_id]);
    }
}

// Función para tomar los tenedores
void pickup_forks(int philosopher_id) {
    sem_wait(&mutex); // Entrar a sección crítica
    
    state[philosopher_id] = HUNGRY;
    printf("🍴 Filósofo %d está HAMBRIENTO\n", philosopher_id);
    fflush(stdout);
    
    test_philosopher(philosopher_id); // Intentar comer
    
    sem_post(&mutex); // Salir de sección crítica
    
    // Esperar hasta poder comer
    sem_wait(&philosophers[philosopher_id]);
}

// Función para soltar los tenedores
void putdown_forks(int philosopher_id) {
    sem_wait(&mutex); // Entrar a sección crítica
    
    state[philosopher_id] = THINKING;
    printf("🤔 Filósofo %d está PENSANDO\n", philosopher_id);
    fflush(stdout);
    
    // Verificar si los vecinos pueden comer ahora
    test_philosopher(left_neighbor(philosopher_id));
    test_philosopher(right_neighbor(philosopher_id));
    
    sem_post(&mutex); // Salir de sección crítica
}

// Función principal del filósofo
void* philosopher(void* arg) {
    int philosopher_id = *(int*)arg;
    
    printf("🧠 Filósofo %d se sentó a la mesa\n", philosopher_id);
    fflush(stdout);
    
    for (int meal = 0; meal < NUM_MEALS; meal++) {
        // Pensar
        printf("🤔 Filósofo %d está pensando...\n", philosopher_id);
        fflush(stdout);
        usleep(rand() % 2000000 + 500000); // Pensar 0.5-2.5 segundos
        
        // Intentar comer
        pickup_forks(philosopher_id);
        
        // Comer
        meals_eaten[philosopher_id]++;
        usleep(rand() % 1500000 + 500000); // Comer 0.5-2 segundos
        
        printf("✅ Filósofo %d terminó de comer (comida %d/%d)\n", 
               philosopher_id, meals_eaten[philosopher_id], NUM_MEALS);
        fflush(stdout);
        
        // Soltar tenedores
        putdown_forks(philosopher_id);
        
        // Pequeña pausa antes de la siguiente iteración
        usleep(rand() % 500000);
    }
    
    printf("🎉 Filósofo %d TERMINÓ todas sus comidas (%d/%d)\n", 
           philosopher_id, meals_eaten[philosopher_id], NUM_MEALS);
    fflush(stdout);
    
    return NULL;
}

// Función para mostrar el estado actual de la mesa
void print_table_status() {
    printf("\n📊 Estado de la mesa:\n");
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        char* status;
        switch (state[i]) {
            case THINKING: status = "PENSANDO"; break;
            case HUNGRY: status = "HAMBRIENTO"; break;
            case EATING: status = "COMIENDO"; break;
        }
        printf("   Filósofo %d: %s (comidas: %d/%d)\n", 
               i, status, meals_eaten[i], NUM_MEALS);
    }
    printf("\n");
}

int main() {
    pthread_t philosophers_threads[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];
    
    // Inicializar semilla para números aleatorios
    srand(time(NULL));
    
    // Inicializar semáforos
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&philosophers[i], 0, 0);
        state[i] = THINKING;
        meals_eaten[i] = 0;
    }
    
    printf("=== Problema de los Filósofos Comensales ===\n");
    printf("Número de filósofos: %d\n", NUM_PHILOSOPHERS);
    printf("Comidas por filósofo: %d\n", NUM_MEALS);
    printf("=========================================\n\n");
    
    // Crear hilos de filósofos
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        if (pthread_create(&philosophers_threads[i], NULL, philosopher, &philosopher_ids[i]) != 0) {
            perror("Error creando hilo filósofo");
            exit(1);
        }
    }
    
    // Mostrar estado periódicamente
    for (int i = 0; i < 10; i++) {
        sleep(2);
        print_table_status();
    }
    
    // Esperar a que terminen todos los filósofos
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers_threads[i], NULL);
    }
    
    printf("\n=== Todos los filósofos terminaron ===\n");
    print_table_status();
    
    // Verificar que todos comieron el número correcto de veces
    int total_meals = 0;
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        total_meals += meals_eaten[i];
    }
    printf("Total de comidas servidas: %d/%d\n", total_meals, NUM_PHILOSOPHERS * NUM_MEALS);
    
    // Limpiar recursos
    sem_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&philosophers[i]);
    }
    
    return 0;
}