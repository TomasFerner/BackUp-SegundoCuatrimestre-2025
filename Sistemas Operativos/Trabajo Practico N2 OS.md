# Problemas: Procesos y Threads

## 1. En el diagrama de estados de un proceso, ¿donde interviene el S.O.? ¿Como debería ser el diagrama para ver todos los procesos y el S.O?

Un proceso es un programa en ejecución. Además del código, un proceso incluye también la actividad actual, que queda representada por el valor del contador de programa y por los contenidos de los registros del procesador. Generalmente, un proceso incluye también la pila del proceso, que contiene datos temporales, y una sección de datos, que contiene variables globales. El proceso puede incluir asimismo, un cúmulo de memoria, que es la memoria que se le asigna dinámicamente al proceso en tiempo de ejecución.

A medida que se ejecuta un proceso, el proceso va cambiando de estado. El estado de un proceso se define, en parte, según la actividad actual de dicho proceso. Cada proceso puede estar en uno de los siguientes estados:
- Nuevo: El proceso es creado
- Corriendo: Las instrucciones están siendo ejecutadas
- Espera: El proceso está esperando que ocurra algún evento.
- Listo: El proceso está esperando ser asignado a la CPU.
- Terminado: El proceso ha finalizado su ejecución.

![[../Atachments/Pasted image 20250830135835.png]]

Es importante remarcar que sólo puede haber un proceso ejecutándose en cualquier procesador en cada instante de tiempo concreto. Sin embargo, puede haber muchos procesos en los estados de espera, listo y terminado.

- El **Sistema Operativo (S.O.) interviene en todas las transiciones**, porque es quien **controla el cambio de estado** de los procesos.  
    Ejemplos:
    - **New → Ready**: el S.O. crea la estructura de PCB (Process Control Block) y coloca al proceso en la cola de listos.
    - **Ready → Running**: el **planificador de CPU (scheduler)** del S.O. selecciona el proceso a ejecutar y hace el _dispatch_ (cambio de contexto).
    - **Running → Waiting**: el proceso ejecuta una syscall bloqueante (ej. I/O). El S.O. lo mueve a la cola de espera.
    - **Waiting → Ready**: el S.O. detecta que la operación terminó (por interrupción de I/O) y lo vuelve a poner en listos.
    - **Running → Ready**: el S.O. lo desaloja si expira su _quantum_ en sistemas con planificación _preemptive_.
    - **Running → Terminated**: el S.O. libera los recursos del proceso.
En resumen: los **estados los define el proceso**, pero las **transiciones las controla el S.O.**.

El diagrama clásico sólo muestra **un proceso individual**. Para mostrar **el conjunto del sistema** deberíamos ampliarlo así:
- **Múltiples procesos en cada estado** → no una sola “bolita” de _Ready_, sino una **cola de listos**, **cola(s) de espera**, etc.
- **El S.O. como un proceso especial (o conjunto de rutinas)** que:
    - Gestiona esas colas.
    - Atiende interrupciones y llamadas al sistema.
    - Ejecuta los módulos de planificación y despacho.
- El **diagrama completo** sería entonces como un **modelo de colas**:
    - Varias colas de _Ready_ y _Waiting_ (según dispositivos o prioridades).
    - Una CPU que puede estar ejecutando **un proceso de usuario** o **el kernel del S.O.** (por interrupción o syscall).
    - Flechas indicando que las **transiciones de un proceso entre estados se producen bajo control del S.O.**

En algunos libros esto se representa como un **diagrama de colas de planificación**:
- Cola de _Ready_.
- Colas de _I/O waiting_.
- CPU (que a veces se dibuja “partida” entre “modo usuario” y “modo kernel”).

## 2. ¿Cuales son, normalmente, los sucesos que llevan a la creación de un proceso? ¿Que pasos lleva a cabo el sistema operativo para crear un nuevo proceso?

Los sucesos que normalmente llevan a la creación de un proceso son provenientes del accionar del usuario, por ejemplo, al ejecutar un programa o solicitar alguna acción sobre los dispositivos de E/S.

Un proceso puede dar origen a diversos procesos nuevos, a través de la llamada al sistema crear
proceso durante la ejecución, algunos ejemplos pueden ser fork() y exec()

Cuando ocurre alguno de los sucesos anteriores, el kernel sigue un conjunto de pasos sistemáticos:
1. **Asignar un identificador único (PID)**
    - Para poder referenciarlo dentro del sistema.
2. **Crear la estructura de control del proceso (PCB, Process Control Block)**
    - Donde se guarda estado, registros, contador de programa, info de memoria, archivos abiertos, prioridad, etc.
3. **Reservar memoria**
    - Espacio para código, datos, pila y heap.
4. **Cargar el programa en memoria**
    - El binario del ejecutable se trae desde disco a memoria principal.
5. **Inicializar el contexto de ejecución**
    - Registros en estado inicial, pila vacía, contador de programa apuntando a la primera instrucción.
6. **Asignar recursos de E/S si corresponden**
    - Descriptores de archivos, dispositivos, sockets, etc.
7. **Enlazarlo en las estructuras de planificación**
    - Insertarlo en la cola de _Ready_ para que el planificador pueda seleccionarlo y darle CPU.

**En síntesis:**
- **Sucesos**: arranque del sistema, ejecución de programas, llamadas de otros procesos, servicios.
- **Pasos del S.O.**: crear PID, PCB, reservar memoria, cargar código, inicializar contexto, asignar recursos, y poner el proceso en _Ready_.

## 3. Pregunta

En el libro “Operating Systems: Concepts, Policies, and Mechanisms” se definen los siguientes estados para un proceso: ejecutando (Ejecución), activo (Listo), bloqueado y suspendido. Un proceso esta bloqueado si esta esperando el permiso para usar un recurso y esta suspendido si esta esperando a que termine una operación sobre un recurso que ya ha conseguido. En muchos sistemas operativos, estos dos estados se unen en el estado de Bloqueado, mientras que el estado de Suspendido representa que el proceso esta en memoria secundaria. Compárense las ventajas de ambos conjuntos de definiciones:

Ventajas de la definición del libro (diferenciar _Bloqueado_ y _Suspendido_ como tipos de espera):
- **Mayor precisión semántica**: diferencia si el proceso aún no consiguió el recurso o si ya lo tiene pero espera que termine la operación.
- **Útil en sistemas con control fino de sincronización**: permite optimizar el planificador según el tipo de espera.
- **Facilita el análisis teórico**: es más claro para explicar qué le falta exactamente al proceso para continuar.

Ventajas de la definición usada en muchos S.O. (Bloqueado unificado, Suspendido = swap):
- **Más simple de implementar**: menos estados internos en las estructuras del kernel.
- **Enfatiza el factor de memoria**: que suele ser crítico en sistemas multiprogramados, ya que suspender implica paginación o swapping.
- **Refleja la práctica real de sistemas modernos**: la distinción entre “esperando permiso” y “esperando respuesta” no suele ser necesaria para el planificador; lo importante es si el proceso está en memoria o no.
- **Eficiencia en el manejo de colas**: todos los procesos que no pueden ejecutar por E/S quedan juntos en “Blocked”, simplificando el scheduling.

El **modelo del libro** es más detallado y conceptual, útil para el estudio académico y análisis de mecanismos de sincronización.
El **modelo práctico de los S.O. actuales** es más simple y orientado a la implementación, privilegiando el criterio de **dónde está el proceso (memoria principal o secundaria)** en lugar de la causa específica de la espera.

## 4. Describa las diferencias entre planificadores de corto, mediano y largo termino.

Cuando la CPU queda inactiva, el sistema operativo debe seleccionar uno de los procesos que se encuentran en la cola de procesos preparados para ejecución. El planificador a corto plazo (o planificador de CPU) lleva acabo esa selección de proceso. El planificador elige uno de los procesos que están en memoria preparados para ejecutarse y asigna a la CPU dicho proceso.

La decisión de planificar el CPU puede tener lugar cuando un proceso:
1. Conmuta de ejecutado a estado de espera
2. Conmuta de ejecutando a estado de listo
3. Conmuta de espera a listo
4. Termina.

En las situaciones 1 y 4, n hay más que una opción en términos de planificación: debe seleccionar un nuevo proceso para su ejecución (si hay alguno). Sin embargo, en las situaciones 2 y 3 si que existe la opción de planificar un nuevo proceso o no.

Planificador de largo plazo (long-term scheduler)
- **Función:** decide **qué programas admitidos al sistema pasarán a ser procesos en memoria** (es decir, controla el grado de multiprogramación).
- **Frecuencia:** se ejecuta con **baja frecuencia** (minutos, incluso horas).
- **Responsabilidad:** seleccionar un buen **mix de procesos** (CPU-bound vs I/O-bound) para optimizar el uso del sistema.
- **Ejemplo:** en un sistema batch, decidir qué jobs de la cola de entrada cargar en memoria para su ejecución.
- **Meta:** controlar la **carga global del sistema**.

 Planificador de mediano plazo (medium-term scheduler)
- **Función:** decide **qué procesos en memoria deben ser suspendidos o reanudados**.
- **Frecuencia:** se ejecuta de manera **intermedia** (segundos o minutos).
- **Responsabilidad:** gestionar el **swapping** (sacar procesos de memoria principal a disco y traerlos de nuevo).
- **Ejemplo:** suspender un proceso que lleva mucho tiempo esperando I/O para liberar memoria y mejorar la respuesta de otros.
- **Meta:** mejorar la **eficiencia de la CPU y la memoria** balanceando la carga.

Planificador de corto plazo (short-term scheduler)
- **Función:** decide **qué proceso listo en memoria principal obtiene la CPU**.
- **Frecuencia:** se ejecuta con **muy alta frecuencia** (milisegundos).
- **Responsabilidad:** hacer el **dispatch** del proceso a ejecutar, aplicando algoritmos como FCFS, RR, SJF, prioridades, etc.
- **Ejemplo:** elegir entre 3 procesos en la cola de _Ready_ cuál se ejecuta a continuación.
- **Meta:** optimizar el **tiempo de respuesta**, el **uso de CPU** y la **equidad entre procesos**.

## 5. Describa las acciones que realiza el kernel cuando cambia el contexto entre procesos.

Una interrupción provoca que el sistema operativo cambie la tarea que actualmente se encuentra en el CPU y ejecuta una rutina del kernel. 

Cuando esto ocurre, el sistema necesita salvar el contexto del proceso que actualmente se encuentra en ejecución de forma tal que pueda restablecerlo cuando el otro proceso haya terminado. El contexto del proceso está representado por su PCB.

Esta tarea es conocida como cambio de contexto. Cuando ocurre este evento, el kernel salva el contexto del proceso antiguo en el PCB y carga el contexto del nuevo proceso a correr. El cambio de contexto representa un overhead en tiempo ya que el sistema no realiza nada útil mientras este transcurre. 

La velocidad con la que se realiza varía de computadora en computadora, dependiendo de la velocidad de la memoria, el número de registros que deben ser copiados y la existencia de instrucciones especiales para tal fin.

- **Guardar el estado del proceso saliente**
    - Se detiene la ejecución del proceso actual.
    - El kernel guarda en su **PCB (Process Control Block)**:
        - Contador de programa (PC).
        - Registros de propósito general.
        - Registros especiales (PSW, flags, etc.).
        - Punteros de pila, mapas de memoria, estado de CPU.
    - Este PCB queda almacenado en la cola correspondiente (_Ready_, _Waiting_, etc.).
- **Actualizar estructuras del sistema operativo**
    - Se marca al proceso saliente con el estado correcto (_Ready_, _Blocked_, etc.).
    - Se actualizan colas de planificación y estructuras de control (ej.: si expiró el quantum, pasa a _Ready_).
- **Seleccionar el nuevo proceso a ejecutar**
    - El **planificador de corto plazo** elige, según el algoritmo (RR, prioridad, etc.), qué proceso en la cola de _Ready_ tomará la CPU.
- **Cargar el estado del proceso entrante**
    - El kernel toma el PCB del proceso elegido.
    - Restaura su contexto:
        - Registros de propósito general.
        - Contador de programa (instrucción a ejecutar).
        - Puntero de pila.
        - Flags/PSW.
- **Cambiar el modo de ejecución**
    - El kernel pasa de **modo kernel** a **modo usuario** para que el proceso elegido continúe su ejecución en espacio de usuario.
- **Reanudar la ejecución del nuevo proceso**
    - La CPU sigue ejecutando la instrucción donde había quedado ese proceso.

Resumen:
- Guardar PCB del proceso saliente.
- Actualizar estructuras del SO.
- Elegir nuevo proceso.
- Restaurar PCB del entrante.
- Cambiar a modo usuario y reanudar.

El cambio de contexto implica **guardar el contexto del proceso actual**, **seleccionar otro proceso** y **restaurar su contexto**.
- **Costoso**: porque no hace trabajo útil de usuario (tiempo de CPU gastado solo en gestión).
- **Necesario**: porque permite la multiprogramación, la concurrencia y la compartición de CPU.

## 6. Problema

La mayor parte de la problemática de la administración del procesador puede describirse con ayuda de un diagrama de transición de estados de los procesos, como el que se expone en la figura 1.

El objetivo de este ejercicio es analizar en detalle las relaciones existentes entre los procesos, las rutinas de atención de interrupciones y el planificador de procesos. Debe describir como interactúan las rutinas de atención de interrupciones, el planificador de procesos y la base de datos necesaria para cumplir con el diagrama de transiciones. O sea, debe indicar: ¿Cuales son los eventos que provocan las transiciones 1, 2, 3 y 4?

![[../Atachments/{98964179-0E4A-487E-997E-A8D343803567}.png]]

- **Running (Corriendo)** → el proceso usa la CPU.
- **Ready (Listo)** → el proceso espera turno para usar la CPU.
- **Waiting/Blocked (Espera)** → el proceso espera la finalización de una operación de E/S u otro evento.

### Transición 1: De Corriendo→Listo

- **Evento:** **Desalojo (preemption)** por parte del sistema operativo.
    - Expiración del **quantum** en un sistema con _time sharing_.
    - Llegada de un proceso con **mayor prioridad** (planificación por prioridades).
- **Mecanismo:** Una **interrupción de reloj** o evento externo provoca que el kernel guarde el contexto del proceso en su PCB, lo marque como _Ready_, y lo coloque en la cola de listos.

### Transición 2: De Listo→Corriendo

- **Evento:** **Selección por el planificador de corto plazo (dispatcher)**.
    - El proceso en _Ready_ es elegido para ejecutarse en la CPU.
- **Mecanismo:** El kernel hace un **cambio de contexto** cargando el PCB del proceso seleccionado, y lo pone en ejecución.
### Transición 3: De Corriendo→Espera

- **Evento:** El proceso ejecuta una **llamada al sistema bloqueante** (ej. petición de I/O, espera de semáforo, read en un socket).
- **Mecanismo:** El kernel detiene al proceso, guarda su contexto, lo mueve a la cola de _Waiting/Blocked_, y transfiere el control a otro proceso listo.
### Transición 4: De Espera→Listo

- **Evento:** **Finalización de la operación de E/S** o liberación del recurso esperado.
    - Ejemplo: una interrupción de disco, de red, de timer o señal de que el semáforo fue liberado. 
- **Mecanismo:** La **rutina de atención de interrupción (ISR)** ejecuta código del kernel que mueve el proceso de la cola de _Waiting_ a la cola de _Ready_.

 **Relación entre los componentes**
- **Rutinas de atención de interrupciones (ISR):**
    - Detectan eventos externos (reloj, E/S) y notifican al kernel.
    - Son las responsables de activar las transiciones 1 y 4 principalmente.
- **Planificador de procesos (scheduler):**
    - Decide qué proceso pasa de _Ready_ a _Running_ (Transición 2).
    - Actúa después de interrupciones o llamadas al sistema.
- **Base de datos (estructuras del S.O.):**
    - **PCB**: guarda contexto, estado, registros.
    - **Cola de listos** y **colas de espera**: almacenan los procesos según su estado.
    - Estas estructuras son manipuladas por el kernel en cada transición.

**En resumen:**
- **Transición 1 (Running → Ready):** interrupción de reloj o desalojo por prioridad.
- **Transición 2 (Ready → Running):** elección del scheduler.
- **Transición 3 (Running → Waiting):** syscall bloqueante (E/S o recurso).
- **Transición 4 (Waiting → Ready):** interrupción que indica fin de E/S o recurso disponible.

## 7. Problema

Suponga que cuatro procesos están ejecutando en un sistema con un solo procesador, las direcciones de inicio de cada uno son las siguientes: 4050, 3200. 5000 y 6700. Las trazas individuales se muestran en el cuadro 1. 

Realice la traza de entrelazado de ejecución de los procesos. Asuma que el dispatcher es invocado cada 5 instrucciones o por una interrupción y el dispatcher ejecuta 4 instrucciones

![[../Atachments/{326E75F6-8BCC-47CB-8FC9-1FCF0574F072}.png]]

## 8. ¿Un proceso puede esperar simultáneamente a mas de un suceso o evento? Justifique su respuesta

- Formalmente, un proceso está bloqueado esperando **una condición definida**.
- Pero esa condición puede ser **“el primero de varios eventos”**, si el sistema operativo ofrece primitivas para espera múltiple.
- Si el sistema no lo soporta, el proceso solo puede esperar a un evento y debe programarse otra lógica (p. ej. multiproceso, señales, polling).

## 9. Problema

Considere el diagrama de estados, que esta formado por siete estados (revise el capıtulo 3 del libro de Stallings). 

Suponga que el dispatcher del sistema operativo tiene que elegir un proceso. Hay procesos en el estado Listo y Listo/Suspendido, y que al menos un proceso en el estado Listo/Suspendido tiene mayor prioridad que cualquiera de los procesos en el estado Listo. Dos políticas diferentes se pueden considerar: 
(1) Siempre se elige un proceso del estado Listo, para reducir al mínimo el intercambio, 
(2) siempre se dará preferencia a los procesos de mayor prioridad.

Sugiera una política intermedia que trate de equilibrar la prioridad y el rendimiento.

**Política de prioridad condicionada por estado y edad:**

1. Se define un **umbral de prioridad** Pmin
2. Si hay un proceso en **Listo/Suspendido** cuya prioridad excede Pmin **y** la diferencia de prioridad respecto al proceso más prioritario en Listo es significativa, entonces se elige ese proceso, incluso si requiere reactivarlo.
3. Si no se cumple la condición, se elige un proceso del estado **Listo** para evitar overhead de intercambio y reactivación.
4. Para evitar inanición de los procesos suspendidos, se puede aplicar un **aging**, aumentando gradualmente su prioridad mientras están suspendidos.

**Resumen conceptual:**
- Se intenta **dar preferencia a la prioridad**, pero **no a cualquier costo**: solo se despierta un proceso suspendido si su prioridad es lo suficientemente alta.
- Los procesos en Listo siguen teniendo ventaja cuando la diferencia de prioridad no es crítica, reduciendo overhead y manteniendo buen rendimiento.
- Se previene la **inanición** mediante aging.

## 10. ¿Como se pueden comunicar los procesos? Brinde un ejemplo en el cual considere necesario que 2 procesos se comuniquen.

Los **procesos** pueden comunicarse porque, aunque cada uno tiene su **espacio de direcciones propio**, muchas veces necesitan **coordinación, compartir datos o sincronizarse**. Esta comunicación se llama **Inter-Process Communication (IPC)**.

Los dos modelos principales son:

1. **Memoria compartida**
    - Los procesos acuerdan usar un **segmento de memoria común** donde pueden leer y escribir datos.
    - Ventaja: rápido, porque no hay copia de datos entre procesos.
    - Desventaja: requiere **sincronización** (por ejemplo, semáforos o mutex) para evitar **condiciones de carrera**.
2. **Pasaje de mensajes**
    - Los procesos **no comparten memoria**, sino que **envían y reciben mensajes** a través del sistema operativo.
    - Puede ser **sincrónico** (el proceso espera al mensaje) o **asincrónico** (el proceso continúa y revisa el mensaje después).
    - Ventaja: más seguro, evita accesos concurrentes directos.
    - Desventaja: generalmente más lento que la memoria compartida.
### Ejemplo práctico

**Caso:** Dos procesos cooperativos: un **sensor de temperatura** y un **sistema de alarma**
- El proceso del **sensor** lee la temperatura cada segundo.
- Si detecta que la temperatura supera un umbral, necesita **notificar inmediatamente** al proceso de la alarma para que se active.

**Cómo se comunican:**

1. **Memoria compartida:**
    - Se define un **buffer compartido** con la última lectura de temperatura.
    - El sensor escribe la temperatura en el buffer y activa un **semáforo** para indicar que hay un dato nuevo.
    - El proceso de alarma espera el semáforo, lee el valor y decide si activa la alarma.
2. **Pasaje de mensajes:**
    - El sensor envía un **mensaje** al sistema de alarma solo cuando la temperatura supera el umbral.
    - La alarma recibe el mensaje y se activa sin necesidad de revisar constantemente la memoria.

## 11. Considere la comunicacion sincronica y asincronica entre procesos. Presente ventajas y desventajas de cada una.

### Comunicación sincrónica

**Definición:**
- El proceso que envía un mensaje **espera hasta que el receptor lo reciba**.
- Ambos procesos se sincronizan en el acto de comunicarse.

**Ventajas:**
- **Simplicidad:** fácil de implementar y de razonar sobre la secuencia de eventos.
- **Coherencia:** el emisor sabe que el receptor recibió el mensaje, evitando pérdida de información.
- **Sincronización implícita:** no necesita mecanismos extra de sincronización, como semáforos.

**Desventajas:**
- **Bloqueo del emisor:** si el receptor no está listo, el emisor se queda esperando, reduciendo el paralelismo.
- **Menor rendimiento:** puede generar tiempos de espera innecesarios si los procesos no están equilibrados.

**Ejemplo:** un sistema bancario donde el proceso de actualización de saldo espera confirmación del proceso de verificación antes de continuar.
### Comunicación asincrónica

**Definición:**
- El proceso que envía un mensaje **no espera** a que el receptor lo reciba; continúa ejecutándose.
- El receptor puede leer el mensaje más tarde.

**Ventajas:**
- **Mayor paralelismo y eficiencia:** los procesos no se bloquean esperando, lo que aprovecha mejor la CPU.
- **Flexibilidad:** útil en sistemas distribuidos donde los procesos pueden estar en distintas máquinas o con distintos ritmos.

**Desventajas:**
- **Complejidad:** requiere **buffers**, colas o mecanismos de notificación.
- **Incertidumbre:** el emisor no sabe inmediatamente si el mensaje fue recibido, lo que puede generar problemas si es crítico.
- **Posible pérdida de mensajes:** si los buffers se llenan o no hay manejo adecuado

**Ejemplo:** un sistema de notificaciones push: el emisor envía mensajes y sigue ejecutando otras tareas mientras los receptores los reciben en su propio tiempo.

## 12. Considere un esquema de comunicaci´on entre procesos basado en mailboxes. a) Suponga un proceso P que desea esperar por dos mensajes, uno desde el mailbox A y el otro desde el mailbox B. ¿Cu´al secuencia de send y receive deber´ıa ejecutar? b) ¿Cual secuencia de send y receive debería ejecutar P si desea esperar por un mensaje del mailbox A o del mailbox B (o de ambos)?

### a) Esperar dos mensajes uno desde A y otro desde B

Si el proceso P **necesita ambos mensajes obligatoriamente**, debe ejecutar **receive** en cada mailbox por separado:

receive(A, messageA)   // espera hasta recibir un mensaje desde A 
receive(B, messageB)   // espera hasta recibir un mensaje desde B`

- Orden: puede ser primero A y luego B, o primero B y luego A, según convenga.
- Lo importante: P **se bloqueará** hasta que cada mailbox entregue su mensaje correspondiente.
- Resultado: P asegura que tiene **ambos mensajes** antes de continuar.
### b) Esperar un mensaje desde A o B (o ambos)

Si P puede continuar cuando **llega un mensaje desde cualquiera de los mailboxes**, se necesita una **recepción selectiva** o verificación de ambos mailboxes:

1. **Polling o select** (si el sistema lo permite):

if message in mailbox A:     
	receive(A, message) 
else if message in mailbox B:     
	receive(B, message)`

2. **Bloqueo hasta que llegue alguno** (en sistemas que permiten `receive` con múltiples fuentes):
receive({A, B}, message)  // espera hasta que llegue un mensaje de A o B`

- Ventaja: no bloquea P hasta recibir **ambos mensajes**, sino que actúa en cuanto llega **cualquiera**.
- Si ambos llegan, se pueden recibir en orden de llegada: primero uno, luego el otro.

## 13. ¿Cuales son las caracterısticas mas importantes de los threads? ¿En que casos los utilizarıa? ¿Cual es la diferencia de los threads a nivel kernel y los que son implementados a nivel usuario?

Un thread (o proceso de peso liviano) es una unidad básica de utilización de la CPU; comprende un contador de programa, un conjunto de registros y una pila. Un thread comparte con sus threads compañeros (colectivamente conocidos como tarea o task) su sección de código, sección de datos y otros recursos del sistema operativo, como los archivos abiertos y las señales. 

Un proceso tradicional o proceso de peso pesado es igual a una tarea con un solo thread.

Las ventajas de la programación multihilo pueden dividirse en cinco categorías principales.

**Capacidad de respuesta:** El uso de múltiples hilos en una aplicación interactiva permite que un programa continúe ejecutándose incluso aunque parte de él esté bloqueado o realizando una operación muy larga, lo que incrementa la capacidad de respuesta al usuario.

**Compartición de recursos:** Por omisión, los hilos comparten la memoria y los
recursos del proceso al que pertenecen. La ventaja de compartir código y los datos es que permite que una aplicación tenga varios hilos de actividad diferentes dentro de un mismo espacio de direcciones

**Economía:** La asignación de memoria y recursos para la creación de procesos es costosa. Dado que los hilos comparten recursos del proceso al que pertenecen, es más económico crear y realizar cambios de contexto entre unos y otros.

**Utilización sobre Arquitecturas Multiprocesador:** Las ventajas de usar configuraciones multihilo pueden verse incrementadas significativamente en una arquitectura multiprocesador, donde los hilos pueden ejecutarse en paralelo en los diferentes procesadores. Los mecanismos multihilo en una máquina con varios CPU incrementan el grado de concurrencia. No obstante, los sistemas multicore ponen desafíos a los programadores tales como: dividir actividades, balance, partición de datos, dependencia de los datos y verificación y depuración

**Escalabilidad**

### Casos en los que usaría _threads_

- **Aplicaciones con tareas concurrentes independientes**:  
    Ejemplo: en un navegador, un thread para la interfaz gráfica, otro para la descarga de archivos, otro para el renderizado.
- **Tareas que comparten memoria**:  
    Ejemplo: un servidor web con múltiples threads atendiendo a diferentes clientes, todos compartiendo la caché en memoria.
- **Programación paralela en multiprocesadores**:  
    Ejemplo: dividir un cálculo numérico pesado en múltiples threads que corren en distintos núcleos.

### Diferencia entre _threads_ a nivel **kernel** y **usuario**

1. **Threads de nivel usuario (User-Level Threads, ULT)**
    - Gestionados por una librería en espacio de usuario (ej. POSIX pthreads en modo user-level).
    - El kernel **no sabe que existen**: solo ve al proceso como una única entidad.
    - **Ventajas**:
        - Creación, destrucción y cambio de contexto muy rápidos.
        - No requieren intervención del kernel.
    - **Desventajas**:
        - Si un thread hace una llamada bloqueante al sistema (ej. I/O), **todo el proceso se bloquea**.
        - No pueden aprovechar múltiples núcleos en sistemas multiprocesador (el kernel solo planifica el proceso como un todo).
2. **Threads de nivel kernel (Kernel-Level Threads, KLT)**
    - El kernel **sí conoce y gestiona cada thread**.
    - Cada thread puede ser planificado de manera independiente.
    - **Ventajas**:
        - Pueden ejecutarse realmente en paralelo en distintos núcleos.
        - Si un thread bloquea, los demás pueden seguir corriendo.
    - **Desventajas**:
        - Creación, destrucción y cambios de contexto son más costosos (requieren intervención del kernel).

## 14. ¿Cuales recursos son utilizados cuando un thread es creado? ¿y en el caso de un proceso?

## Recursos que se usan al crear un **thread**

Cuando se crea un thread dentro de un proceso, **hereda casi todos los recursos del proceso** (espacio de direcciones, archivos abiertos, variables globales, etc.), pero necesita algunos propios:

- **Pila propia (stack):**  
    Cada hilo necesita una pila independiente para manejar sus llamadas a funciones y variables locales.
- **Registros de CPU (contexto):**  
    Se guarda el estado de ejecución del hilo: contador de programa (PC), registros generales, puntero de pila.
- **Control Block del thread (TCB, Thread Control Block):**  
    Una estructura de datos (en kernel o en user space, según el modelo) donde se mantiene:
    - ID del hilo
    - Estado del hilo (running, ready, blocked, etc.)
    - Prioridad
    - Puntero a la pila
    - Información de scheduling

**No se duplican recursos pesados** (espacio de direcciones, código, archivos), porque se comparten entre todos los hilos del proceso.
### Comparación directa
- **Crear un thread** → mucho más liviano, porque solo requiere una pila + TCB.
- **Crear un proceso** → mucho más costoso, porque requiere un espacio de direcciones completo + PCB + estructuras del kernel asociadas.

## 15. Proporcione dos ejemplos de programación en los que los mecanismos de multithread no proporcionen un mejor rendimiento que una solución monitoread.

## Ejemplo 1: Programa con **tareas completamente secuenciales**

- Si un problema tiene **dependencias fuertes entre pasos**, no podés dividirlo en hilos que avancen en paralelo.
- Ejemplo: calcular el valor de Fibonacci con el algoritmo iterativo:  
    Cada número depende del anterior → no podés calcular `F(n)` sin tener `F(n-1)` y `F(n-2)`
- En este caso, dividir en threads solo agrega **overhead de creación, sincronización y cambios de contexto**, sin paralelismo útil.
## Ejemplo 2: Programa con **tareas muy pequeñas o rápidas**

- Si el trabajo de cada hilo es mínimo, el **tiempo extra** que consume el sistema en:
    - Crear los hilos
    - Sincronizarlos (locks, semáforos, barreras)
    - Gestionar el scheduler  
        supera al beneficio del paralelismo.
- Ejemplo: un programa que solo hace una suma de 100 números enteros.  
    → Dividirlo en 4 hilos para que cada uno sume 25 elementos es **menos eficiente** que hacerlo directamente en un bucle monohilo.

**Tareas inherentemente secuenciales** (dependencias de datos muy fuertes).
**Tareas muy pequeñas/rápidas**, donde el _overhead_ del multihilo supera al beneficio.

## 16. Una solución multithreaded utilizando threads a nivel de usuario, ¿presenta mejor rendimiento (performance) en un sistema multiprocesador que en un sistema monoprocesador?

- Una solución multithreaded con hilos a nivel de usuario **NO mejora su rendimiento en un sistema multiprocesador frente a un monoprocesador**, porque el kernel no puede repartirlos en distintos núcleos.
- La única ventaja está en **sistemas monoprocesador**, donde permite simular concurrencia con menos overhead que threads a nivel kernel.
## 17. ¿Es posible tener concurrencia pero no paralelismo? Explique

### Concurrencia

- Significa que **varias tareas están “vivas” al mismo tiempo**, aunque no necesariamente se ejecuten literalmente al mismo tiempo.
- Se logra cuando el sistema operativo (o el runtime) va **intercalando la ejecución** de tareas, de modo que avanzan “en paralelo lógico”.
- Ejemplo: en un sistema monoprocesador, el scheduler asigna el CPU a un proceso/hilo por unos milisegundos, luego a otro, y así sucesivamente. Para el usuario, parece que ambos corren a la vez
### Paralelismo

- Significa que **dos o más tareas se ejecutan físicamente al mismo tiempo**, en procesadores/núcleos distintos.
- Requiere hardware con múltiples unidades de ejecución (multicore, multiprocesador, GPU, etc.).
### ¿Es posible concurrencia sin paralelismo?

✅ **Sí.**

- En un **sistema monoprocesador**, se pueden tener varios hilos concurrentes (el SO los va cambiando con _time-sharing_).
- Pero como solo hay un CPU, **no hay paralelismo real**: en cada instante solo se ejecuta una tarea.
- El usuario lo percibe como simultáneo, pero en realidad es alternado.


## 18. Considere un sistema multiprocesador y un programa multithreaded utilizando el modelo de threads muchos-a-muchos. Sea la cantidad de threads a nivel usuario mayor que la cantidad de procesadores en el sistema. 

Discuta sobre el rendimiento en las siguientes situaciones:
### a) La cantidad de kernel threads alocados al programa es menor que la cantidad de procesadores. 
**KLT < número de procesadores**
- Algunos procesadores del sistema quedarán **ociosos**, porque el scheduler solo tiene menos hilos de kernel para repartir que CPUs disponibles.
- **Resultado:** **mal rendimiento** → desaprovechamiento del paralelismo del multiprocesador.
### b) La cantidad de kernel threads alocados al programa es igual a la cantidad de procesadores.
**KLT = número de procesadores**
- Ahora cada procesador puede ejecutar un KLT.
- **Se aprovecha el hardware al 100%** (todos los procesadores trabajando).
- El rendimiento es **óptimo en términos de utilización de CPU**, aunque hay que tener en cuenta el overhead de la multiplexación de muchos ULT sobre los mismos KLT.
- **Resultado:** **buen rendimiento balanceado**.
### c) La cantidad de kernel threads alocados al programa es superior a la cantidad de procesadores pero menor que la cantidad de threads a nivel de usuario.
**KLT > número de procesadores pero KLT < número de ULT**
- Hay más hilos de kernel que procesadores, por lo que el kernel deberá planificarlos en los procesadores disponibles (time-sharing).
- Esto puede **aumentar el overhead de cambios de contexto** en el kernel.
- Sin embargo, permite que si un KLT se bloquea (ej. por I/O), otros KLT puedan seguir ejecutándose en paralelo.
- Como aún hay más ULT que KLT, sigue habiendo multiplexación, pero con **más flexibilidad** que en el caso (b).
- **Resultado:**
    - Mejor tolerancia a bloqueos que en (b).
    - Peor eficiencia de CPU por overhead extra si la cantidad de KLT crece demasiado.