# Ejercicio 1: Comunicación entre procesos mediante pipe()

En este ejercicio se implementa la comunicación entre un proceso padre y un proceso hijo utilizando un pipe en C.

## Pasos realizados

1. **Creación del pipe:**  
   Se utiliza la función `pipe()` para crear un canal de comunicación unidireccional entre dos procesos.

2. **Creación del proceso hijo:**  
   Se utiliza `fork()` para crear un proceso hijo. Ambos procesos (padre e hijo) comparten el pipe.

3. **Comunicación:**
   - El **proceso padre** cierra el extremo de lectura del pipe y escribe varios mensajes en el extremo de escritura.
   - El **proceso hijo** cierra el extremo de escritura y lee los mensajes enviados por el padre desde el pipe.

4. **Procesamiento de los mensajes:**  
   El hijo procesa los mensajes recibidos, separándolos por el carácter nulo (`\0`) y los muestra por pantalla.

## ¿Por qué se cierran los extremos de lectura y escritura?

Cada proceso cierra el extremo del pipe que no utiliza para evitar errores y liberar recursos:
- El **padre** solo escribe, por lo que cierra el extremo de lectura.
- El **hijo** solo lee, por lo que cierra el extremo de escritura.

Cerrar los extremos no utilizados también es importante para que las operaciones de lectura y escritura funcionen correctamente. Por ejemplo, si el hijo no cierra el extremo de escritura, la función `read()` podría no detectar el final de los datos enviados por el padre.

## ¿Cómo funciona un pipe en su implementación?

Un pipe es un mecanismo de comunicación que permite transferir datos de un proceso a otro de manera unidireccional. Internamente, el sistema operativo crea un buffer en memoria y dos descriptores de archivo:
- Uno para **lectura**
- Uno para **escritura**

Cuando un proceso escribe datos en el pipe, estos se almacenan en el buffer. El otro proceso puede leer esos datos desde el buffer utilizando el descriptor de lectura. Los pipes son especialmente útiles para la comunicación entre procesos relacionados, como un padre y su hijo.

## Objetivo

El objetivo es demostrar cómo se puede enviar información desde un proceso padre a un proceso hijo usando pipes, permitiendo el envío de múltiples mensajes de manera eficiente y ordenada.

---

# Ejercicio 2: Comunicación bidireccional con dos pipes

En este ejercicio se implementa la comunicación en ambos sentidos entre un proceso padre y un proceso hijo utilizando dos pipes.

## Pasos realizados

1. **Creación de dos pipes:**  
   Se crean dos pipes: uno para enviar mensajes del padre al hijo (`pipe1`) y otro para enviar mensajes del hijo al padre (`pipe2`).

2. **Creación del proceso hijo:**  
   Se utiliza `fork()` para crear un proceso hijo. Ambos procesos comparten los descriptores de ambos pipes.

3. **Comunicación:**
   - El **padre** cierra los extremos que no utiliza (lectura de `pipe1` y escritura de `pipe2`). Luego, escribe un mensaje en `pipe1` para que lo reciba el hijo y espera la respuesta leyendo de `pipe2`.
   - El **hijo** cierra los extremos que no utiliza (escritura de `pipe1` y lectura de `pipe2`). Lee el mensaje del padre desde `pipe1`, lo muestra por pantalla y luego responde escribiendo en `pipe2`.

4. **Cierre de los pipes:**  
   Ambos procesos cierran los extremos de los pipes que utilizaron una vez finalizada la comunicación para liberar recursos y señalar el fin de la transmisión.

## ¿Cómo funciona la comunicación bidireccional con pipes?

Cada pipe es unidireccional, por lo que se necesitan dos pipes para lograr comunicación en ambos sentidos. De esta manera, uno de los pipes se utiliza para enviar datos del padre al hijo y el otro para la respuesta del hijo al padre.  
Esto permite que ambos procesos puedan intercambiar mensajes de forma ordenada y controlada, simulando una conversación.

## Objetivo

El objetivo es demostrar cómo se puede implementar una comunicación bidireccional entre dos procesos usando dos pipes, permitiendo que ambos procesos puedan enviar y recibir mensajes entre sí.

---

# Ejercicio 3: Uso de colas de mensajes

En este ejercicio se implementa la comunicación entre un proceso padre y un proceso hijo utilizando una cola de mensajes del sistema.

## Pasos realizados

1. **Definición de la estructura del mensaje:**  
   Se define una estructura que contiene un campo `long mtype` (tipo de mensaje) y un array de caracteres para el texto del mensaje.

2. **Creación de la cola de mensajes:**  
   Se utiliza `ftok()` para generar una clave única y `msgget()` para crear la cola de mensajes o acceder a ella si ya existe.

3. **Comunicación:**
   - El **proceso padre** prepara un mensaje, asigna el tipo y el texto, y lo envía a la cola usando `msgsnd()`.
   - El **proceso hijo** recibe el mensaje desde la cola usando `msgrcv()` y lo muestra por pantalla.

4. **Eliminación de la cola:**  
   Una vez finalizada la comunicación, el padre elimina la cola de mensajes con `msgctl(..., IPC_RMID, ...)` para liberar los recursos del sistema.

## ¿Cómo funciona una cola de mensajes?

Una cola de mensajes es un mecanismo de comunicación proporcionado por el sistema operativo que permite a los procesos intercambiar mensajes de manera asíncrona.  
Cada mensaje tiene un tipo (`mtype`) que permite seleccionar qué mensajes recibir. Los mensajes se almacenan en la cola hasta que un proceso los recibe, lo que permite que los procesos no tengan que ejecutarse al mismo tiempo para comunicarse.

## Objetivo

El objetivo es demostrar cómo se puede enviar y recibir mensajes entre procesos usando colas de mensajes, facilitando la comunicación y sincronización entre procesos.

---

# Ejercicio 4: Comunicación múltiple con colas de mensajes

En este ejercicio se simula la comunicación entre múltiples procesos escritores y múltiples procesos lectores utilizando colas de mensajes del sistema.

## Pasos realizados

1. **Definición de la estructura del mensaje:**  
   Se utiliza una estructura con un campo `long mtype` (tipo de mensaje) y un array de caracteres para el texto.

2. **Creación de la cola de mensajes:**  
   Se genera una clave única con `ftok()` y se crea la cola con `msgget()`.

3. **Creación de procesos escritores:**  
   Se crean varios procesos escritores (por ejemplo, 3). Cada escritor envía un mensaje a la cola con un tipo diferente (`mtype = i + 1`).

4. **Creación de procesos lectores:**  
   Se crean varios procesos lectores (por ejemplo, 2). Cada lector espera y recibe un mensaje de un tipo específico usando `msgrcv()`.

5. **Sincronización y limpieza:**  
   El proceso padre espera a que todos los hijos terminen y luego elimina la cola de mensajes con `msgctl(..., IPC_RMID, ...)`.

## ¿Cómo funciona la comunicación múltiple con colas de mensajes?

Cada escritor envía un mensaje con un tipo distinto. Los lectores esperan mensajes de un tipo específico, de modo que cada lector recibe el mensaje correspondiente a su tipo.  
Esto permite distribuir mensajes entre varios procesos de manera controlada y flexible, facilitando la comunicación entre múltiples productores (escritores) y consumidores (lectores).

## Objetivo

El objetivo es demostrar cómo se pueden coordinar varios procesos para enviar y recibir mensajes de manera selectiva usando colas de mensajes, permitiendo la comunicación múltiple y sincronizada

---

# Ejercicio 5: Comunicación mediante memoria compartida

En este ejercicio se implementa la comunicación entre un proceso padre y un proceso hijo utilizando un segmento de memoria compartida.

## Pasos realizados

1. **Creación de la clave y el segmento de memoria compartida:**  
   Se utiliza `ftok()` para generar una clave única y `shmget()` para crear un segmento de memoria compartida de tamaño suficiente para un entero.

2. **Creación del proceso hijo:**  
   Se utiliza `fork()` para crear un proceso hijo. Ambos procesos pueden acceder al segmento de memoria compartida.

3. **Comunicación:**
   - El **proceso padre** se conecta al segmento con `shmat()`, escribe un número entero y luego se desconecta con `shmdt()`.
   - El **proceso hijo** se conecta al mismo segmento con `shmat()`, lee el número escrito por el padre y luego se desconecta con `shmdt()`.

4. **Eliminación del segmento:**  
   El padre elimina el segmento de memoria compartida con `shmctl(..., IPC_RMID, ...)` después de que el hijo haya leído el valor.

## ¿Cómo funciona la memoria compartida?

La memoria compartida es un mecanismo eficiente de comunicación entre procesos, ya que ambos pueden acceder directamente a una región de memoria común.  
Esto permite transferir datos de manera rápida y sin necesidad de copiar información entre procesos. Es fundamental sincronizar el acceso para evitar condiciones de carrera, aunque en este ejemplo simple el padre escribe antes de que el hijo lea.

## Objetivo

El objetivo es demostrar cómo se puede crear y utilizar un segmento de memoria compartida para intercambiar información entre procesos, usando las funciones `shmget()`, `shmat()`, `shmdt()` y `shmctl()`.