/*
3. Uso de colas de mensajes
Objetivo: Crear una cola de mensajes, enviar y recibir mensajes entre procesos.
Resuelva:
Crear una estructura con long mtype y un array de caracteres.
Usar msgget() para crear la cola.
El padre env´ıa un mensaje con msgsnd().
El hijo recibe y muestra el mensaje con msgrcv().
Sugerencia: Usar msgctl(..., IPC RMID, ...) para eliminar la cola
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

// Definición de la estructura del mensaje
struct msg {
    //mtype es un identificador numérico que categoriza el mensaje dentro de la cola
    long mtype;
    //mtext es el contenido real del mensaje, que en este caso es una cadena de caracteres de hasta 100 bytes
    char mtext[100];
};

int main(){
    //Crea clave unica para la cola, parametros (ruta, id)
    key_t key = ftok(".", 'A');

    //Crea la cola de mensajes, parametros (llave, permisos de lectura y escritura)
    int msqid = msgget(key, IPC_CREAT | 0666);
    
    pid_t pid = fork();

    //Identificador de la cola de mensajes
    struct msg mensaje;
    
    //Chequeo de errores
    check_error(key, "Error en ftok");
    check_error(msqid, "Error en msgget");
    check_error(pid, "Error en el fork, no es el hijo ni el padre");
    
    if(pid > 0){//Proceso padre
        mensaje.mtype = 1; //Tipo de mensaje
        strcpy(mensaje.mtext, "Hola hijo, este es un mensaje por cola.\n");
        
        //Envio del mensaje a la cola, parametros (id de la cola, puntero al mensaje, tamaño del mensaje, flags)
        int hayError = msgsnd(msqid, &mensaje, strlen(mensaje.mtext) + 1, 0);
        check_error(hayError, "Error en msgsnd");

        wait(NULL); // Espera al hijo

        //Elimina la cola de mensajes, parametros (id de la cola, IPC_RMID para eliminar, NULL)
        msgctl(msqid, IPC_RMID, NULL);
    }

    if(pid == 0){//Proceso hijo
        //Hijo lee el mensaje de la cola, parametros (id de la cola, puntero al mensaje, tamaño del mensaje, tipo de mensaje a leer, flags)
        int hayError = msgrcv(msqid, &mensaje, sizeof(mensaje.mtext), 1, 0);
        check_error(hayError, "Error en msgrcv");
        printf("HIJO: Mensaje recibido del padre: %s\n",mensaje.mtext);
    }

    return 0;
}