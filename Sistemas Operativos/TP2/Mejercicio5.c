/*
5. Comunicación mediante memoria compartida
Objetivo: Crear y utilizar un segmento de memoria compartida.
Resuelva:
Usar shmget() para crear un segmento.
El padre escribe un número entero en la memoria.
El hijo accede a la memoria y muestra el valor.
Funciones: shmget(), shmat(), shmdt(), shmctl(). Sugerencia: Utilizar ftok() para generar la clave
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

void check_error(int result, const char* msg) {
    if(result < 0) {
        perror(msg);
        exit(EXIT_FAILURE);
    }
}

int main() {
    int key = ftok(".", 'B'); //Crea clave unica para la memoria compartida
     //Crea el segmento de memoria compartida
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    int *shared_memory;
    pid_t pid = fork();

    //Chequeo de errores
    check_error(key, "Error en ftok");
    check_error(shmid, "Error en shmget");
    check_error(pid, "Error en el fork, no es el hijo ni el padre");

    if(pid > 0){//Proceso padre
        int numero = 42; //Numero a escribir en la memoria compartida
        shared_memory = shmat(shmid, NULL, 0); //Adjunta el segmento de memoria compartida
        *shared_memory = numero; //Escribe el numero en la memoria compartida
        
        printf("PADRE: Escribi el numero %d en la memoria compartida\n", numero);
        shmdt(shared_memory); //Desadjunta el segmento de memoria compartida
        wait(NULL); 
    } 
    
    if (pid == 0) {//Proceso hijo
        sleep(1); //Asegura que el padre escriba primero
        shared_memory = (int*) shmat(shmid, NULL, 0); //Adjunta el segmento de memoria compartida
        
        printf("HIJO: Leí el numero %d de la memoria compartida\n", *shared_memory);
        shmdt(shared_memory); //Desadjunta el segmento de memoria compartida
        shmctl(shmid, IPC_RMID, NULL); //Elimina el segmento de memoria compartida
    }

    return 0;

}
