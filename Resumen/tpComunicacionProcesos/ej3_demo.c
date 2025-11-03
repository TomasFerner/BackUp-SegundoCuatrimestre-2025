//Demostración de comportamiento bloqueante de msgrcv()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mensaje {
    char texto[100];
};

int main(){
    int id_cola;
    struct mensaje msg;
    pid_t pid;
    
    key_t clave = ftok(".", 65);
    if(clave == -1){
        perror("ftok");
        exit(EXIT_FAILURE);
    }

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
        //Proceso hijo: ESPERA 3 segundos antes de enviar
        printf("Hijo: Voy a esperar 3 segundos antes de enviar...\n");
        sleep(3);
        
        strcpy(msg.texto, "Mensaje después de 3 segundos");
        printf("Hijo: Enviando mensaje ahora...\n");
        if(msgsnd(id_cola, &msg, sizeof(msg.texto), 0)== -1){
                perror("msgsnd hijo");
                exit(EXIT_FAILURE);
        }
        printf("Hijo: Mensaje enviado\n");
        exit(EXIT_SUCCESS);
    } 
    else {
        //Proceso padre: Intenta recibir INMEDIATAMENTE
        printf("Padre: Intentando recibir mensaje INMEDIATAMENTE...\n");
        printf("Padre: (Si no hay mensaje, me voy a BLOQUEAR hasta que llegue)\n");
        
        if(msgrcv(id_cola, &msg, sizeof(msg.texto), 0, 0) == -1){
            perror("msgrcv padre");
            exit(EXIT_FAILURE);
        }
        printf("Padre: ¡Mensaje recibido!: %s\n", msg.texto);
        
        wait(NULL);
        
        if(msgctl(id_cola, IPC_RMID, NULL) == -1){
            perror("msgctl");
            exit(EXIT_FAILURE);
        }
        printf("Cola eliminada\n");
    }
    return 0;
}
