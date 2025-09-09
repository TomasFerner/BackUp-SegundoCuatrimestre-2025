#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MSG_SIZE 100
#define NUM_MSGS 3

int main() {
    int fd[2];
    pid_t pid;
    char *mensajes[NUM_MSGS] = {
        "Mensaje 1 del padre al hijo\n",
        "Mensaje 2 del padre al hijo\n",
        "Mensaje 3 del padre al hijo\n"
    };

    if (pipe(fd) == -1) {
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
        close(fd[0]); // Cierra el extremo de lectura
        for (int i = 0; i < NUM_MSGS; i++) {
            write(fd[1], mensajes[i], strlen(mensajes[i]) + 1); // Incluye el '\0'
        }
        close(fd[1]); // Cierra el extremo de escritura
    } else {
        // Proceso hijo
        close(fd[1]); // Cierra el extremo de escritura
        char buffer[MSG_SIZE];
        int n;
        while ((n = read(fd[0], buffer, MSG_SIZE)) > 0) {
            int start = 0;
            for (int i = 0; i < n; i++) {
                if (buffer[i] == '\0') {
                    printf("Hijo recibió: %s", &buffer[start]);
                    start = i + 1;
                }
            }
        }
        close(fd[0]);
    }
    return 0;
}