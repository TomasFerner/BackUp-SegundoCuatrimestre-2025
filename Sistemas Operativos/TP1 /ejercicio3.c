#include <stdio.h>
#include <unistd.h>   // fork(), execlp()
#include <sys/wait.h> // wait()

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error en fork");
        return 1;
    }

    if (pid == 0) {
        // Proceso hijo: reemplaza su código ejecutando "ls -l"
        printf("Hijo: ejecutando 'ls -l'\n");
        execlp("ls", "ls", "-l", NULL);
        // Si execlp falla:
        perror("Error en execlp");
        return 1;
    } else {
        // Proceso padre: espera a que el hijo termine
        wait(NULL);
        printf("Padre: el hijo terminó.\n");
    }
    return 0;
}