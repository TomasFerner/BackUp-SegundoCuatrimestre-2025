//Suma paralela de filas de una matriz utilizando hilos
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/mman.h>
#include <unistd.h>

void* sumar_fila(void* arg){
    int* fila = (int*)arg;
    long suma = 0;
    for(int i = 0; i < 5; i++){
        suma = suma + fila[i];
    }
    return (void*)(long)suma;
}

int main(){
    int matris[5][5] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };
    long sumaTotal = 0;
    pthread_t hilos[5];
    pthread_create(&hilos[0], NULL, sumar_fila, (void*)&matris[0]);
    pthread_create(&hilos[1], NULL, sumar_fila, (void*)&matris[1]);
    pthread_create(&hilos[2], NULL, sumar_fila, (void*)&matris[2]);
    pthread_create(&hilos[3], NULL, sumar_fila, (void*)&matris[3]);
    pthread_create(&hilos[4], NULL, sumar_fila, (void*)&matris[4]);

    for(int i = 0; i < 5;i++){
        void* resultadoIntermedio = 0;
        pthread_join(hilos[i],&resultadoIntermedio);
        sumaTotal = sumaTotal + (long)resultadoIntermedio;
    }
    printf("La suma total de la matriz es: %ld\n", sumaTotal);
    return 0;
}