//Crea M hilos con pthread-create(), cada hilo imprime su identificador y el de su hilo padre.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_t hilo_padre; // Variable global para almacenar el ID del hilo padre

// Función que ejecutará cada hilo
void* funcion_hilo(void* arg) {
    int numero_hilo = *((int*)arg);
    pthread_t mi_id = pthread_self();
    
    printf("Hilo %d con ID %lu creado por el hilo padre %lu\n", 
           numero_hilo, mi_id, hilo_padre);
    return NULL;
}

int main(){
    int m = 5; // Número de hilos a crear
    pthread_t hilos[m];
    int numeros[m]; // Array para pasar el número de cada hilo
    
    hilo_padre = pthread_self(); // Guardar el ID del hilo padre
    
    for(int i = 0; i < m; i++){
        numeros[i] = i + 1; // Numeramos los hilos del 1 al m
        pthread_create(&hilos[i], NULL, funcion_hilo, &numeros[i]);
    }

    for(int i = 0; i < m; i++){
        pthread_join(hilos[i], NULL);
    }
    printf("Hilo padre %lu espero que terminen los hilos hijos\n", hilo_padre);

    return 0;
}