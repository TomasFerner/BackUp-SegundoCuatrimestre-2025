/*
2. Comunicaci´on bidireccional con dos pipes
Objetivo: Implementar comunicaci´on en ambos sentidos entre dos procesos.
Resuelva:
Crear dos pipes.
El padre env´ıa un mensaje al hijo (pipe 1).
El hijo responde al padre (pipe 2).
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

void check_error(int result, const char* msg) {
    if(result < 0) {
        perror(msg);
        exit(EXIT_FAILURE);
    }
}

int main(){
    //Creas 2 pipes para comunicacion bidireccional
    int pipe1[2]; //Pipe del padre al hijo
    int pipe2[2]; //Pipe del hijo al padre

    check_error(pipe(pipe1), "Error en el pipe1");
    check_error(pipe(pipe2), "Error en el pipe2");

    pid_t pid = fork();
    check_error(pid, "Error en el fork, no es el hijo ni el padre");

    if(pid > 0){
        //Proceso padre
        const char* mensaje1 = "Hola hijo como estas soy tu padre";
        printf("Soy el proceso padre y voy a enviar un mensaje\n");
        close(pipe1[0]);
        write(pipe1[1],mensaje1,strlen(mensaje1)+1);
        close(pipe1[1]);
        
        char buffer[100];
        close(pipe2[1]);
        read(pipe2[0],buffer,sizeof(buffer));
        printf("PADRE: Mensaje recibido del hijo: %s\n",buffer);
        close(pipe2[0]);
    }   

    wait(NULL);

    if (pid == 0){
        //Proceso hijo
        char buffer[100];
        const char* mensaje2 = "Hola padre, estoy bien, soy tu hijo";
        close(pipe1[1]);
        read(pipe1[0], buffer, sizeof(buffer));
        printf("HIJO: Mensaje recibido del padre: %s\n",buffer);
        printf("Soy el proceso hijo y voy a enviar un mensaje\n");
        close(pipe1[0]);

        memset(buffer, 0, sizeof(buffer)); //Limpio el buffer

        close(pipe2[0]);
        write(pipe2[1],mensaje2,strlen(mensaje2)+1);
        close(pipe2[1]);
    }
    return 0;
}