//Multiples hilos ejecutan operacion matematicas diferentes y guardan resultados en la misma variable
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/mman.h>
#include <unistd.h>

#define N 5

// Mutex para sincronizar acceso a la variable compartida
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* funcion_hilo_1(void* arg){
    int* v = (int*)arg;  // arg recibe &valor
    pthread_mutex_lock(&mutex);
    *v = *v + 1;         // Modifica el valor original
    printf("Hilo 1: %d + 1 = %d\n", *v - 1, *v);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* funcion_hilo_2(void* arg){
    int* v = (int*)arg;
    pthread_mutex_lock(&mutex);
    int anterior = *v;
    *v = *v * 2;
    printf("Hilo 2: %d * 2 = %d\n", anterior, *v);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* funcion_hilo_3(void* arg){
    int* v = (int*)arg;
    pthread_mutex_lock(&mutex);
    *v = *v - 1;
    printf("Hilo 3: %d - 1 = %d\n", *v + 1, *v);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* funcion_hilo_4(void* arg){
    int* v = (int*)arg;
    pthread_mutex_lock(&mutex);
    int anterior = *v;
    *v = *v / 2;
    printf("Hilo 4: %d / 2 = %d\n", anterior, *v);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* funcion_hilo_5(void* arg){
    int* v = (int*)arg;
    pthread_mutex_lock(&mutex);
    int anterior = *v;
    *v = *v * *v;
    printf("Hilo 5: %d * %d = %d\n", anterior, anterior, *v);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(){
    int valor = 10; // Valor inicial diferente de 0 para ver mejor los cambios
    pthread_t hilos[N];

    printf("Valor inicial: %d\n", valor);

    // Crear hilos - pasar la dirección de memoria de valor
    pthread_create(&hilos[0], NULL, funcion_hilo_1, &valor);
    //              ↑         ↑     ↑              ↑
    //              │         │     │              └─ Parámetro: dirección de 'valor'
    //              │         │     └─ Función: suma 1
    //              │         └─ Atributos: por defecto
    //              └─ Donde guardar ID del hilo 1
    pthread_create(&hilos[1], NULL, funcion_hilo_2, &valor);
    pthread_create(&hilos[2], NULL, funcion_hilo_3, &valor);
    pthread_create(&hilos[3], NULL, funcion_hilo_4, &valor);
    pthread_create(&hilos[4], NULL, funcion_hilo_5, &valor);

    // Esperar a que terminen los hilos
    for(int i=0; i<N; i++){
        pthread_join(hilos[i], NULL);
    }

    printf("Valor final: %d\n", valor);
    
    // Destruir el mutex
    pthread_mutex_destroy(&mutex);
    
    return 0;
}