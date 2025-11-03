//Usar un pipe creandolo con pipe() para enviar datos desde un proceso padre a un proceso hijo y de vuelta

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){
    int pipeHijoPadre[2]; //Descriptor necesario para el pipe  
    int pipePadreHijo[2]; //Descriptor necesario para el pipe
    if (pipe(pipeHijoPadre) == -1) {
        perror("Error al crear el pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipePadreHijo) == -1) {
        perror("Error al crear el pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid;

    pid = fork(); //Crear proceso hijo
    if(pid < 0){
        perror("Error al crear el proceso hijo");
        exit(EXIT_FAILURE); 
    }
    
    if(pid == 0){
        //Proceso hijo
        char mensaje[] = "Hola desde el proceso hijo!";
        close(pipeHijoPadre[0]);//cerrar el extremo de lectura
        printf("Proceso hijo enviando mensaje al padre \n");
        write(pipeHijoPadre[1], mensaje, strlen(mensaje) + 1);
        close(pipeHijoPadre[1]);//cerrar el extremo de escritura
    }
    else{
        //Proceso padre
        close(pipeHijoPadre[1]);//cerrar el extremo de escritura
        char mensajeRecibido[100];
        read(pipeHijoPadre[0], mensajeRecibido, sizeof(mensajeRecibido));
        printf("Proceso padre recibio mensaje: %s\n", mensajeRecibido);
        close(pipeHijoPadre[0]);//cerrar el extremo de lectura
    }

    if(pid == 0){
        //proceso hijo
        close(pipePadreHijo[1]);//cerrar el extremo de escritura
        char mensajeRecibido[100];
        read(pipePadreHijo[0], mensajeRecibido, sizeof(mensajeRecibido));
        printf("Proceso hijo recibio mensaje: %s\n", mensajeRecibido);
        close(pipePadreHijo[0]);//cerrar el extremo de lectura
    }
    else{
        //proceso padre
        char mensaje2[] = "Hola desde el proceso padre!";
        close(pipePadreHijo[0]);//cerrar el extremo de lectura
        printf("Proceso padre enviando mensaje al hijo \n");
        write(pipePadreHijo[1], mensaje2, strlen(mensaje2) + 1);
        close(pipePadreHijo[1]);//cerrar el extremo de escritura
        wait(NULL); //Esperar a que el proceso hijo termine
    }


    return 0;
}