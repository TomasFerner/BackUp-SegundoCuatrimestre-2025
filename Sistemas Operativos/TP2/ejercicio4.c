#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MSG_SIZE 100
#define N_ESCRITORES 3
#define N_LECTORES 2

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
    key = ftok(".", 'B');
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

    // Crear N_ESCRITORES procesos escritores
    for (int i = 0; i < N_ESCRITORES; i++) {
        pid = fork();
        if (pid == 0) {
            // Proceso escritor
            msg.mtype = i + 1; // Cada escritor usa un tipo diferente
            snprintf(msg.mtext, MSG_SIZE, "Mensaje del escritor %d\n", i + 1);
            if (msgsnd(msqid, &msg, strlen(msg.mtext) + 1, 0) == -1) {
                perror("msgsnd");
                exit(EXIT_FAILURE);
            }
            exit(0);
        }
    }

    // Crear N_LECTORES procesos lectores
    for (int i = 0; i < N_LECTORES; i++) {
        pid = fork();
        if (pid == 0) {
            // Proceso lector
            long tipo = i + 1; // Cada lector espera un tipo específico
            if (msgrcv(msqid, &msg, MSG_SIZE, tipo, 0) == -1) {
                perror("msgrcv");
                exit(EXIT_FAILURE);
            }
            printf("Lector %d recibió: %s", i + 1, msg.mtext);
            exit(0);
        }
    }

    // Proceso padre espera a todos los hijos
    for (int i = 0; i < N_ESCRITORES + N_LECTORES; i++) {
        wait(NULL);
    }

    // Elimina la cola de mensajes
    msgctl(msqid, IPC_RMID, NULL);
    
    return 0;
}