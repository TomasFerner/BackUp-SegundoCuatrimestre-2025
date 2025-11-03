//Crear una cola de mensajes, enviar y recibir mensajes entre procesos.
//el hijo envia un mensaje y espera respuesta del padre, el padre recibe el mensaje y responde
//luego hijo agradece y termina
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Definición de la estructura del mensaje
struct mensaje {
    char texto[100]; // Texto del mensaje
};

int main(){
    int id_cola;
    struct mensaje msg;
    pid_t pid;
    
    //Crear una clave para la cola de mensajes
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

    pid = fork();
    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if(pid == 0){
        //Proceso hijo: enviar mensaje y luego recibir respuesta
        strcpy(msg.texto, "Hola desde el proceso hijo");
        if(msgsnd(id_cola, &msg, sizeof(msg.texto), 0)== -1){
                perror("msgsnd hijo");
                exit(EXIT_FAILURE);
        }
        printf("Proceso hijo: Mensaje enviado\n");
        
        // Hijo recibe respuesta del padre
        if(msgrcv(id_cola, &msg, sizeof(msg.texto), 0, 0) == -1){
            perror("msgrcv hijo");
            exit(EXIT_FAILURE);
        }
        printf("Proceso hijo: Respuesta recibida: %s\n", msg.texto);

        strcpy(msg.texto, "Gracias por recibir mi mensaje");
        if(msgsnd(id_cola, &msg, sizeof(msg.texto), 0)== -1){
                perror("msgsnd hijo");
                exit(EXIT_FAILURE);
        }
        printf("Proceso hijo: Mensaje de agradecimiento enviado\n");
        exit(EXIT_SUCCESS);
    } 
    else {
        //Proceso padre: recibir mensaje y enviar respuesta
        if(msgrcv(id_cola, &msg, sizeof(msg.texto), 0, 0) == -1){
            perror("msgrcv padre");
            exit(EXIT_FAILURE);
        }
        printf("Proceso padre: Mensaje recibido: %s\n", msg.texto);
        
        // Padre envía respuesta al hijo
        strcpy(msg.texto, "Respuesta desde el proceso padre");
        if(msgsnd(id_cola, &msg, sizeof(msg.texto), 0)== -1){
                perror("msgsnd padre");
                exit(EXIT_FAILURE);
        }
        printf("Proceso padre: Respuesta enviada\n");
        
        if(msgrcv(id_cola, &msg, sizeof(msg.texto), 0, 0) == -1){
            perror("msgrcv padre");
            exit(EXIT_FAILURE);
        }
        printf("Proceso padre: Mensaje de agradecimiento recibido: %s\n", msg.texto);

        wait(NULL); //Esperar a que el hijo termine
        
        // Eliminar la cola de mensajes
        if(msgctl(id_cola, IPC_RMID, NULL) == -1){
            perror("msgctl");
            exit(EXIT_FAILURE);
        }
        printf("Cola de mensajes eliminada\n");
    }
    return 0;
}