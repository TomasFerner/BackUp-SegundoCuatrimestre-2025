/*
4. Comunicacion múltiple con colas de mensajes
Objetivo: Simular múltiples escritores y lectores usando colas de mensajes.
Resuelva:
Crear N procesos escritores que envían mensajes.
Un proceso lector recibe y muestra los mensajes.
Extienda para que haya varios lectores que esperan un mensaje de algún tipo específico.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

void check_error(int result, const char* msg) {
    if(result < 0) {
        perror(msg);
        exit(EXIT_FAILURE);
    }
}

struct msg {
    long mtype;
    char mtext[100];
};

int main(){
    int key = ftok(".", 'A');//Crea clave unica para la cola
    int msqid = msgget(key, IPC_CREAT | 0666);//Crea la cola de mensajes
    pid_t pid  = fork();
    struct msg mensaje;
    int N = 5; //Cantidad de procesos escritores

    //Chequeo de errores
    check_error(key, "Error en ftok");
    check_error(msqid, "Error en msgget");      
    check_error(pid, "Error en el fork, no es el hijo ni el padre");

    for(int i = 0; i < N; i++){
        if(fork() == 0){
            // Procesos escritores hijos
            mensaje.mtype = 1; // Tipo de mensaje
            snprintf(mensaje.mtext, sizeof(mensaje.mtext), "Hola soy el proceso escritor %d y con proces id %d", i+1, getpid());
            int hayError = msgsnd(msqid, &mensaje, sizeof(mensaje.mtext), 0);
            check_error(hayError, "Error en msgsnd");
            exit(0);
        }
    }

    if(pid > 0){//Proceso lector padre
        for(int i = 0; i < N; i++){
            //Recibe N mensajes
            msgrcv(msqid, &mensaje, sizeof(mensaje.mtext), 0, 0);
            printf("Mensaje recibido: %s\n", mensaje.mtext);
        }
    }

    // Esperar a que todos los hijos terminen y eliminar la cola
    while (wait(NULL) > 0);
    msgctl(msqid, IPC_RMID, NULL);

    return 0;
}
