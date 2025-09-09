Ej 1:
Declara la variable pid para almacenar el identificador del proceso.
Ejecuta fork() para clonar el proceso actual, creando un proceso hijo.
Verifica si la clonación fue exitosa comprobando si pid < 0.
Ambos procesos (padre e hijo) continúan ejecutándose en paralelo:
El hijo entra en el bloque if (pid == 0), imprime su información, espera 2 segundos y luego indica que terminó.
El padre entra en el bloque else, imprime su información y luego ejecuta wait(NULL); para esperar a que el hijo termine.
Solo después de que el hijo termina, el padre imprime el mensaje indicando que detectó que el hijo finalizó

Ej 2:
Este programa en C demuestra cómo un proceso padre puede crear múltiples procesos hijos utilizando la llamada al sistema fork() en un bucle.

El número de procesos hijos a crear (N) se pasa como argumento en la línea de comandos.

Cada hijo imprime:

Su PID (identificador único de proceso).

El PID de su padre (getppid()).

Luego termina inmediatamente.

El proceso padre utiliza waitpid() para esperar la finalización de todos los hijos y confirmar su terminación.

TODOS SON HIJOS CLONES DEL MISMO PADRE

De esta manera, el programa muestra cómo se crean y gestionan procesos en un sistema operativo tipo Unix/Linux.

Ej 3:
Este programa crea un nuevo proceso hijo usando fork(). 
El proceso hijo reemplaza su propio código y ejecuta el comando ls -l (que muestra el listado detallado de archivos en el directorio actual) usando la función execlp(). 

La función execlp reemplaza el programa que está ejecutando el proceso actual por otro programa. En este caso, dentro del proceso hijo, execlp("ls", "ls", "-l", NULL); hace que el proceso deje de ejecutar el código en C y pase a ejecutar el comando ls -l.

El primer argumento es el nombre del programa a buscar en el PATH ("ls"), seguido por los argumentos que se le pasan al programa ("ls", "-l"), y termina con NULL para indicar el final de la lista de argumentos. 
Si execlp funciona correctamente, el código que sigue después de su llamada no se ejecuta, porque el proceso ya está corriendo el nuevo programa. Si hay un error, execlp devuelve -1 y se ejecuta el código siguiente (en este caso, el mensaje de error).

Mientras tanto, el proceso padre espera a que el hijo termine su ejecución con wait(NULL). 
Cuando el hijo termina, el padre imprime un mensaje indicando que el hijo finalizó. 
Así, el programa muestra cómo un proceso puede crear un hijo y hacer que este ejecute otro programa diferente.

Ej 4:
Este programa crea 5 hilos, cada uno imprime su número de identificación y un mensaje, y el programa principal espera a que todos terminen antes de finalizar.

el programa se compila con: 
gcc ejercicio4.c -o ejercicio4 -lpthread

esto ya que el flag -lpthread le indica al compilador que incluya la biblioteca de hilos necesaria para pthread_create y pthread_join

Ej5:
Comunicación:
Se utiliza memoria compartida para que los procesos hijos escriban sus sumas parciales y el padre las lea

Los hilos comparten el mismo espacio de memoria, por lo que pueden escribir directamente en variables globales.

Resumen de comunicación:

Procesos: Necesitan mecanismos explícitos como memoria compartida, pipes, etc., porque cada proceso tiene su propio espacio de memoria.

Hilos: Comparten el mismo espacio de memoria, por lo que pueden comunicarse fácilmente usando variables globales o estructuras compartidas.