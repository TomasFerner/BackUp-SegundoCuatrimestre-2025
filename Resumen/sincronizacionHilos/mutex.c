#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Variable compartida
int variable_compartida = 0;

// Mutex para exclusión mutua
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Función que ejecutarán los hilos
void* modificar_variable(void* arg) {
    int* shared_counter = (int*)arg;
    
    // Sección crítica
    pthread_mutex_lock(&mutex);
    
    // Incrementar el contador compartido para generar ID único
    (*shared_counter)++;
    int id_hilo = *shared_counter;
    
    printf("Hilo %d: Accediendo a la variable (valor actual: %d)\n", id_hilo, variable_compartida);
    
    // Simular trabajo
    sleep(1);
    
    // Modificar la variable
    variable_compartida += 10;
    
    printf("Hilo %d: Variable modificada a %d\n", id_hilo, variable_compartida);
    
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

int main() {
    pthread_t hilos[3];
    int contador_hilos = 0; // Inicializar en 0
    
    printf("Proceso padre: Iniciando programa con variable = %d\n", variable_compartida);
    
    // Crear 3 hilos - todos acceden a la misma dirección
    for (int i = 0; i < 3; i++) {
        if (pthread_create(&hilos[i], NULL, modificar_variable, &contador_hilos) != 0) {
            perror("Error al crear hilo");
            exit(1);
        }
        printf("Proceso padre: Hilo %d creado\n", i + 1);
    }
    
    // Esperar a que todos los hilos terminen
    for (int i = 0; i < 3; i++) {
        if (pthread_join(hilos[i], NULL) != 0) {
            perror("Error al esperar hilo");
            exit(1);
        }
        printf("Proceso padre: Hilo %d terminado\n", i + 1);
    }
    
    // El padre imprime el valor final
    printf("\nProceso padre: Valor final de la variable = %d\n", variable_compartida);
    printf("Proceso padre: Total de hilos que accedieron = %d\n", contador_hilos);
    
    // Destruir el mutex
    pthread_mutex_destroy(&mutex);
    
    return 0;
}