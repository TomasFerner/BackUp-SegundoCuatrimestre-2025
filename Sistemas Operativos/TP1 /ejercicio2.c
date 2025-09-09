#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // fork(), getpid(), getppid()
#include <sys/wait.h> // waitpid()

int main(int argc, char *argv[]) {
    /*
     argc (argument count): cantidad de argumentos que recibe el programa
     argv (argument vector): vector (array) de cadenas con los argumentos

     Ejemplo de ejecución:
        ./multiprocesos 5
        -> argc = 2
        -> argv[0] = "./multiprocesos"  (nombre del programa)
        -> argv[1] = "5"                (argumento pasado por el usuario)
    */

    if (argc != 2) {
        // stderr: flujo de error estándar (file descriptor 2). 
        // Se usa para mostrar mensajes de error, independiente de la salida normal (stdout).
        fprintf(stderr, "Uso: %s <N>\n", argv[0]);
        return 1;
    }

    // atoi (ASCII to Integer): convierte una cadena (char*) a un número entero (int).
    int N = atoi(argv[1]); 
    if (N <= 0) {
        fprintf(stderr, "N debe ser un número positivo\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Error en fork");
            return 1;
        }

        if (pid == 0) {
            // Código del hijo
            printf("Hijo %d: PID=%d, PPID=%d\n", i+1, getpid(), getppid());
            exit(0); // Importante: el hijo finaliza aquí para no crear más hijos en el bucle
        }
    }

    // Código del padre: esperar a que terminen TODOS los hijos
    for (int i = 0; i < N; i++) {
        int status;
        // waitpid(-1, &status, 0) -> espera a cualquier hijo (-1 indica "cualquiera")
        pid_t hijo_terminado = waitpid(-1, &status, 0);

        if (hijo_terminado > 0) {
            if (WIFEXITED(status)) {
                // WIFEXITED(status): verdadero si el hijo terminó normalmente
                // WEXITSTATUS(status): obtiene el valor de retorno del hijo (exit code)
                printf("El padre detecta que terminó el hijo con PID=%d (exit code=%d)\n",
                       hijo_terminado, WEXITSTATUS(status));
            }
        }
    }

    printf("Todos los hijos terminaron. Padre finaliza.\n");
    return 0;
}
