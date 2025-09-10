#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

/*
1. Comunicacion entre procesos mediante pipe()
Objetivo: Usar un pipe para enviar datos desde un proceso padre a un proceso hijo.
Resuelva:
Crear un pipe con pipe() (Recuerde cerrar los extremos no utilizados).
El proceso padre escribe una cadena de texto en el pipe.
El hijo lee el contenido del pipe y lo muestra por pantalla.
Extienda el ejercicio anterior para permitir enviar m´ultiples mensajes.
*/

void check_error(int result, const char* msg) {
    if(result < 0) {
        perror(msg);
        exit(EXIT_FAILURE);
    }
}

int main(){
    /*
    fd[0]: extremo de lectura.
    fd[1]: extremo de escritura.
    */
    int fd[2];
    pid_t pid;
    
    check_error(pipe(fd), "Error en el pipe");
    check_error(pid = fork(), "Error en el fork, no es el hijo ni el padre");

    if(pid > 0){
        //Mensaje como array con puntero no modificable
        const char* mensaje = "Hola hijo, soy tu padre!";
        printf("Soy el proceso padre y voy a enviar un mensaje\n");
        close(fd[0]); //Cierro el extremo de lectura del pipe, no lo uso
        write(fd[1],mensaje, strlen(mensaje)+1);//strlen(mensaje)+1) para enviar el tamaño del mensaje incluyendo el '\0' que es el final de cadena
        close(fd[1]); //Cierro el extremo de escritura del pipe, ya envie el mensaje
    }
    else if(pid == 0){
        printf("Soy el proceso hijo\n");
        char buffer[100];
        close(fd[1]); //Cierro el extremo de escritura del pipe, no lo uso
        read(fd[0], buffer, sizeof(buffer));
        printf("Mensaje recibido del padre: %s\n", buffer);
        close(fd[0]); // Cierro el extremo de lectura del pipe, ya leí el mensaje
    }
    return 0;
}