#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    key_t key;
    int shmid;
    int *shared_num;
    pid_t pid;

    // Crear clave única para la memoria compartida
    key = ftok(".", 'C');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Crear segmento de memoria compartida
    shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        shmctl(shmid, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        // Proceso padre: escribe un número en la memoria compartida
        shared_num = (int *)shmat(shmid, NULL, 0);
        if (shared_num == (void *)-1) {
            perror("shmat padre");
            shmctl(shmid, IPC_RMID, NULL);
            exit(EXIT_FAILURE);
        }
        *shared_num = 42;
        printf("Padre escribió el número: %d\n", *shared_num);
        shmdt(shared_num);
        wait(NULL); // Espera al hijo
        shmctl(shmid, IPC_RMID, NULL); // Elimina el segmento
    } else {
        // Proceso hijo: lee el número de la memoria compartida
        sleep(1); // Asegura que el padre escriba primero
        shared_num = (int *)shmat(shmid, NULL, 0);
        if (shared_num == (void *)-1) {
            perror("shmat hijo");
            exit(EXIT_FAILURE);
        }
        printf("Hijo leyó el número: %d\n", *shared_num);
        shmdt(shared_num);
        exit(0);
    }

    return 0;
}