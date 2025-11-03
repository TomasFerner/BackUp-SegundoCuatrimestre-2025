#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main() {
    // Crear una clave para la memoria compartida
    key_t key = ftok(".", 1);
    if (key == -1) {
        perror("Error al crear la clave");
        exit(1);
    }
    
    // Crear un segmento de memoria compartida para un entero
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("Error al crear memoria compartida");
        exit(1);
    }
    
    // Adjuntar la memoria compartida al proceso
    int* variable_compartida = (int*)shmat(shmid, NULL, 0);
    if (variable_compartida == (int*)-1) {
        perror("Error al adjuntar memoria compartida");
        exit(1);
    }
    
    // Inicializar la variable compartida
    *variable_compartida = 10;

    printf("Proceso padre: Variable inicial = %d\n", *variable_compartida);

    // Crear proceso hijo
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("Error al crear proceso hijo");
        exit(1);
    }
    
    if (pid == 0) {
        // Código del proceso hijo
        printf("Proceso hijo: Valor actual de la variable = %d\n", *variable_compartida);
        
        // El hijo modifica la variable
        *variable_compartida = 25;
        printf("Proceso hijo: Variable modificada a = %d\n", *variable_compartida);
        
        // Desadjuntar memoria compartida del proceso hijo
        if (shmdt(variable_compartida) == -1) {
            perror("Error al desadjuntar memoria compartida en hijo");
            exit(1);
        }
        
        exit(0);
    } else {
        // Código del proceso padre
        // Esperar a que el hijo termine
        wait(NULL);
        
        // El padre imprime la variable después de que el hijo la modificó
        printf("Proceso padre: Variable después de modificación del hijo = %d\n", *variable_compartida);

        // Desadjuntar memoria compartida del proceso padre
        if (shmdt(variable_compartida) == -1) {
            perror("Error al desadjuntar memoria compartida en padre");
            exit(1);
        }
        
        // Eliminar el segmento de memoria compartida
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("Error al eliminar memoria compartida");
            exit(1);
        }
        
        printf("Memoria compartida eliminada exitosamente\n");
    }
    
    return 0;
}
