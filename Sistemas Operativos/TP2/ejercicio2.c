#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MSG_SIZE 100

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid;
    char buffer[MSG_SIZE];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        // Proceso padre
        close(pipe1[0]); // Cierra lectura de pipe1
        close(pipe2[1]); // Cierra escritura de pipe2

        char *mensaje_padre = "Hola hijo, ¿cómo estás?\n";
        write(pipe1[1], mensaje_padre, strlen(mensaje_padre) + 1);

        read(pipe2[0], buffer, MSG_SIZE);
        printf("Padre recibió: %s", buffer);

        close(pipe1[1]);
        close(pipe2[0]);
    } else {
        // Proceso hijo
        close(pipe1[1]); // Cierra escritura de pipe1
        close(pipe2[0]); // Cierra lectura de pipe2

        read(pipe1[0], buffer, MSG_SIZE);
        printf("Hijo recibió: %s", buffer);

        char *mensaje_hijo = "Hola padre, estoy bien.\n";
        write(pipe2[1], mensaje_hijo, strlen(mensaje_hijo) + 1);

        close(pipe1[0]);
        close(pipe2[1]);
    }
    return 0;
}