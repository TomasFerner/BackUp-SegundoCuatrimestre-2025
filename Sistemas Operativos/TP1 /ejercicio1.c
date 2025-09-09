#include <stdio.h>
#include <unistd.h>   // fork(), getpid(), getppid(), sleep()
#include <sys/wait.h> // wait()

/*
Ambos procesos (padre e hijo) imprimirán su PID y el PID de su padre.
El orden no es siempre el mismo, porque depende de la planificación del sistema operativo 
(el scheduler decide qué proceso corre primero).
Si ponés sleep() en el hijo, verás que el padre imprime antes y luego espera al hijo.
Con wait(), el padre siempre espera al hijo antes de imprimir su mensaje final, garantizando el orden correcto
*/
int main() {
    /*
    Declaración de variable para el PID
    la variable almacena un identificador de proceso. 
    El valor de un pid_t es un número entero que el sistema operativo asigna de manera única 
    a cada proceso en ejecución.
    */
    pid_t pid;

    /*
    La función fork() se utiliza para crear un proceso hijo duplicando el proceso actual (el padre). 
    Si fork() funciona correctamente, devuelve dos valores diferentes: 
    en el proceso padre devuelve el PID del hijo (un número positivo), y en el proceso hijo devuelve 0
    */
    pid = fork();

    if (pid < 0) {
        // Error en fork
        perror("Error en fork");
        return 1;
    }

    if (pid == 0) {
        // Código del hijo
        printf("Soy el HIJO: PID=%d, PPID=%d\n", getpid(), getppid());
        sleep(2); // retardo para ver el orden
        printf("El hijo termina.\n");
    } else {
        //dado que pid > 0 entonces es el padre
        printf("Soy el PADRE: PID=%d, PPID=%d\n", getpid(), getppid());
        /*
        El argumento de wait() es un puntero a un entero donde, si lo deseas, 
        el sistema puede guardar el estado de salida del hijo. 
        Si pasas NULL, simplemente le dices al sistema que no necesitas esa información. 
        Por lo tanto, NULL nunca "se vuelve" otra cosa; solo significa "no quiero el estado de salida".
        */
        // Esperar a que el hijo termine
        wait(NULL);
        printf("El padre detecta que el hijo terminó.\n");
    }
    return 0;
}