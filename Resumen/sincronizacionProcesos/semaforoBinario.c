#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>
#define N 9

int main() {
    // Crear memoria compartida para los semáforos
    sem_t *sem_a = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, 
                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_t *sem_b = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, 
                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_t *mutex_sem = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE,
                           MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
    if (sem_a == MAP_FAILED || sem_b == MAP_FAILED || mutex_sem == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    
    // Inicializar semáforos
    // sem_a = 1 (proceso A puede empezar)
    // sem_b = 0 (proceso B debe esperar)  
    // mutex_sem = 1 (mutex libre)
    if (sem_init(sem_a, 1, 1) == -1 || sem_init(sem_b, 1, 0) == -1 || 
        sem_init(mutex_sem, 1, 1) == -1) {
        perror("sem_init");
        exit(1);
    }
    
    pid_t pid = fork();
    
    if (pid == 0) {
        // Proceso hijo - ejecuta A
        for (int i = 0; i < N; i++) {
            sem_wait(sem_a);        // Esperar turno de A
            
            // SECCIÓN CRÍTICA con semáforo binario como mutex
            sem_wait(mutex_sem);
            printf("A");
            fflush(stdout);
            sem_post(mutex_sem);
            // FIN SECCIÓN CRÍTICA
            
            sem_post(sem_b);        // Dar turno a B
        }
    } else if (pid > 0) {
        // Proceso padre - ejecuta B
        for (int i = 0; i < N; i++) {
            sem_wait(sem_b);        // Esperar turno de B
            
            // SECCIÓN CRÍTICA con semáforo binario como mutex
            sem_wait(mutex_sem);
            printf("B");
            fflush(stdout);
            sem_post(mutex_sem);
            // FIN SECCIÓN CRÍTICA
            
            sem_post(sem_a);        // Dar turno a A
        }
        
        wait(NULL);
        printf("\n");
        
        // Limpiar recursos
        sem_destroy(sem_a);
        sem_destroy(sem_b);
        sem_destroy(mutex_sem);
        munmap(sem_a, sizeof(sem_t));
        munmap(sem_b, sizeof(sem_t));
        munmap(mutex_sem, sizeof(sem_t));
    } else {
        perror("fork");
        exit(1);
    }
    
    return 0;
}