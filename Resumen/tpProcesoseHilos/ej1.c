//Programa donde se crea un proceso hijo los 2 imprimen su pid y el de su padre, avisando quienes son
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid;
    pid = fork();
    if(pid < 0){
        printf("Error al crear el proceso hijo\n");
        exit(-1);
    }

    if(pid == 0){
        printf("Soy el proceso hijo, mi PID es %d y el PID de mi padre es %d\n", getpid(), getppid());
        
    }
    else{
        wait(NULL); //Esperar a que el proceso hijo termine;
        printf("Soy el proceso padre, mi PID es %d y el PID de mi hijo es %d\n", getpid(), pid);
    }

}