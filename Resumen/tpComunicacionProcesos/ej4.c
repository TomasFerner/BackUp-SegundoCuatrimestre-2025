//Simular N multiples escritores y  M lectores usando colas de mensajes.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mensaje {
    char texto[100];   // Texto del mensaje
};

int main(){

    int N = 5; // Cantidad de escritores
    int M = 4; // Cantidad de lectores

    int id_cola;
    struct mensaje msg;
    pid_t pid;

    key_t clave = ftok(".", 65);  // Usar el directorio actual
    if(clave == -1){
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    //Crear la cola de mensajes
    id_cola = msgget(clave, 0666 | IPC_CREAT);
    if(id_cola == -1){
        perror("msgget");
        exit(EXIT_FAILURE); 
    }

    // Inicializar semilla para números aleatorios
    srand(time(NULL));

    // Crear N escritores
    for(int i = 0; i < N; i++){
        pid = fork();
        if(pid < 0){
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if(pid == 0){
            // Proceso escritor
            // Generar número aleatorio de mensajes (entre 1 y 10)
            int num_mensajes = rand() %  10 + 1;
            printf("Escritor %d: Voy a enviar %d mensajes\n", i+1, num_mensajes);
            
            for(int k = 0; k < num_mensajes; k++){
                snprintf(msg.texto, sizeof(msg.texto), "Escritor %d - Mensaje %d", i+1, k+1);
                if(msgsnd(id_cola, &msg, sizeof(msg.texto), 0) == -1){
                    perror("msgsnd escritor");
                    exit(EXIT_FAILURE);
                }
                printf("Escritor %d: Mensaje %d enviado\n", i+1, k+1);

            }
            exit(EXIT_SUCCESS);
        }
    }
    // Crear M lectores
    for(int j = 0; j < M; j++){
        pid = fork();
        if(pid < 0){
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if(pid == 0){
            // Proceso lector
            int mensajes_leidos = 0;
            while(msgrcv(id_cola, &msg, sizeof(msg.texto), 0, IPC_NOWAIT) != -1){
                mensajes_leidos++;
                printf("Lector %d: Mensaje recibido: %s\n", j+1, msg.texto);
                usleep(50000); // Pequeña pausa para visualizar mejor
            }
            printf("Lector %d: Leí %d mensajes. No hay más mensajes, terminando\n", j+1, mensajes_leidos);
            exit(EXIT_SUCCESS);
        }
    }

    // Esperar a que terminen todos los procesos
    for(int i = 0; i < N + M; i++){
        wait(NULL);
    }

    // Eliminar la cola de mensajes
    msgctl(id_cola, IPC_RMID, NULL);

    return 0;
}