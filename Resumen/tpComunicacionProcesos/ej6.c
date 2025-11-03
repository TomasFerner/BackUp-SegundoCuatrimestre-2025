//Dividir el trabajo entre procesos e integrar los resultados usando memoria compartida
/*Resuelva:
El padre crea un arreglo de enteros en memoria compartida.
Crea N procesos que suman distintas partes del arreglo
Cada hijo indica que parte sum´o y el resultado.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <time.h>
#include <string.h>

int main(){
    //4 procesos hijos que sumen partes de un arreglo de 40 enteros
    int N = 4;
    int size = 40;
    int arr[size];

    //inicializar el arreglo con valores aleatorios
    srand(time(NULL));
    for(int i=0; i<size; i++){
        arr[i] = rand() % 10; //valores entre 0 y 9
    }
    //crear memoria compartida para el arreglo y los resultados parciales
    int* shm_arr = mmap(NULL, size * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int* shm_results = mmap(NULL, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if(shm_arr == MAP_FAILED || shm_results == MAP_FAILED){
        perror("mmap");
        exit(1);
    }

    //copiar el arreglo a la memoria compartida
    memcpy(shm_arr, arr, size * sizeof(int));
    
    pid_t pids[N];
    for(int i=0;i<N; i++){
        pids[i] = fork();
        if(pids[i] < 0){
            perror("fork");
            exit(1);
        }
        if(pids[i] == 0){
            //proceso hijo
            int start = i * (size / N);
            int end = (i + 1) * (size / N);
            int partial_sum = 0;
            for(int j=start; j<end; j++){
                partial_sum += shm_arr[j];
            }
            shm_results[i] = partial_sum;
            printf("Hijo %d sumo desde %d hasta %d: %d\n", i, start, end - 1, partial_sum);
            exit(0);
        }
    }

    //esperar a que terminen los hijos
    for(int i=0; i<N; i++){
        waitpid(pids[i], NULL, 0);
    }

    //sumar los resultados parciales
    int total_sum = 0;
    for(int i=0; i<N; i++){
        total_sum += shm_results[i];
    }
    printf("Suma total: %d\n", total_sum);

    //liberar memoria compartida
    munmap(shm_arr, size * sizeof(int));
    munmap(shm_results, N * sizeof(int));

    return 0;
}
