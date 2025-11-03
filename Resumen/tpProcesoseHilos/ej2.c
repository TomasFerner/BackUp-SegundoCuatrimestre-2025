//Programa donde se crea N procesos hijos que imprimen su pid y el de su padre, avisando quienes son
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int N = 5; //Numero de procesos hijos a crear
    pid_t pid;
    for(int i = 0; i < N;i++){
        pid = fork();
        if(pid < 0){
            printf("Error al crear el proceso hijo\n");
            exit(-1);
        }

        if(pid == 0){
            //Proceso hijo
            printf("Soy el proceso hijo %d, mi PID es %d y el PID de mi padre es %d\n", i+1, getpid(), getppid());
            exit(0); //Terminar el proceso hijo
        }
        else{
            wait(NULL); //Esperar a que el proceso hijo termine;
        }
    }
}