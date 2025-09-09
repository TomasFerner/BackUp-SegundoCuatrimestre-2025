#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MSG_SIZE 100

// Definición de la estructura del mensaje
struct mensaje {
    long mtype;
    char mtext[MSG_SIZE];
};

int main() {
    key_t key;
    int msqid;
    pid_t pid;
    struct mensaje msg;

    // Crear clave única para la cola
    key = ftok(".", 'A');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Crear la cola de mensajes
    msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        msgctl(msqid, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        // Proceso padre: envía mensaje
        msg.mtype = 1;
        strcpy(msg.mtext, "Hola hijo, este es un mensaje por cola.\n");
        if (msgsnd(msqid, &msg, strlen(msg.mtext) + 1, 0) == -1) {
            perror("msgsnd");
            msgctl(msqid, IPC_RMID, NULL);
            exit(EXIT_FAILURE);
        }
        wait(NULL); // Espera al hijo
        msgctl(msqid, IPC_RMID, NULL); // Elimina la cola
    } else {
        // Proceso hijo: recibe mensaje
        if (msgrcv(msqid, &msg, MSG_SIZE, 1, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
        printf("Hijo recibió: %s", msg.mtext);
    }
    return 0;
}