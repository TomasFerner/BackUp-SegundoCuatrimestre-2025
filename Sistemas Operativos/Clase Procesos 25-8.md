Material relacionado: [[Clase Estructura del sistema operativo 20-8]]
## Conceptos de procesos

Un ejecutable NO es un proceso

Un SO ejecuta una variedad de programas:
	Sistema Batch-jobs
	Sistemas de tiempo compartido - programas de usuario o tareas

**Proceso**: Un programa en ejecución

Un Proceso incluye:
	contador de programa
	stack
	sección de datos
	texto(código ejecutable)

![[../Atachments/Pasted image 20250825102003.png]]

El **dispatcher** es el componente del **planificador de CPU (CPU scheduler)** encargado de realizar el **cambio de contexto** entre procesos, es decir, de poner en ejecución al proceso que el planificador seleccionó.

En otras palabras:
- El **planificador de CPU** decide **qué proceso** se ejecutará a continuación.
- El **dispatcher** se encarga de **hacer el cambio real** en el procesador para que ese proceso efectivamente comience (o reanude) su ejecución.

Un $proceso$ cambia de estado durante su ejecución.
**nuevo**: el proceso es creado. 
**corriendo** (ejecutando): las instrucciones están siendo ejecutadas. 
**espera**: el proceso está esperando que ocurra algún evento. 
**listo**: el proceso está esperando ser asignado a la CPU. 
**terminado**: el proceso ha finalizado su ejecución.

![[../Atachments/Pasted image 20250825102723.png]]


### ¿Cómo puede obtener el estado de los procesos en el sistema operativo que está utilizando?

El **PCB: Process Control Block** es una estructura de dato que contiene información asociada con cada proceso. 
	- Estado de Proceso 
	- Contador de Programa 
	- Registros de CPU 
	- Información de planificación de CPU 
	- Información de administración de memoria
	- Información contable 
	- Información de estado E/S 

![[../Atachments/Pasted image 20250825103242.png]]
## Planificación de Proceso

### Colas de Planificación de Procesos

**Cola de Job (o tareas)** – conjunto de todos los procesos en el sistema. 
**Cola de listos** – conjunto de todos los procesos residentes en memoria principal, listos y esperando para ejecutar. 
**Colas de dispositivos** – conjunto de procesos esperando por una E/S en un dispositivo de E/S. 
**Migración de procesos** entre las colas.

![[../Atachments/Pasted image 20250825103939.png]]

### Planificadores de Procesos

**Planificador de largo término (o planificador de jobs)** – selecciona que procesos deberían ser puestos en la cola de listos. 
**Planificador de corto término (o planificador de CPU)** – selecciona que procesos deberían ser próximamente ejecutados y colocados en la CPU. 
**Planificador de mediano término** – es parte de la función de swapping

El planificador de **largo término** es invocado poco frecuentemente (segundos, minutos) y puede ser muy lento
	El planificador de largo término controla el grado de multiprogramación. 

El planificador de **corto término** es invocado muy frecuentemente (nanosegundos, microsegundos) y debe ser rápido

Los procesos pueden ser descriptos como:
	- **Procesos limitados por E/S**: pasa más tiempo haciendo E/S que computaciones, ráfagas de CPU muy cortas.
	- **Procesos limitados por CPU**: pasa más tiempo haciendo computaciones que E/S, ráfagas de CPU muy largas.

![[../Atachments/Pasted image 20250825104605.png]]

### Cambio de contexto

Cuando la CPU conmuta a otro proceso, el sistema debe salvar el estado del viejo proceso y cargar el estado para el nuevo proceso vía un cambio de contexto. 
- El contexto de un proceso está representado en el PCB
- El tiempo que lleva el cambio de contexto es sobrecarga; el sistema no hace trabajo útil mientras está conmutando. 
- El tiempo depende del soporte de hardware.

![[../Atachments/Pasted image 20250825104824.png]]

## Operaciones sobre Procesos

### Creación de Procesos

Actividades 
1. Asignar un identificador de proceso único al proceso. 
2. Reservar espacio para proceso. 
3. Inicializar el PCB. 
4. Establecer los enlaces apropiados. 
5. Crear o expandir otras estructuras de datos.

- Espacio de direcciones 
	o El hijo duplica el del padre. 
	o El hijo tiene un programa cargado en él. 
- Procesos padres crean procesos hijos, lo cuales, a su vez crean otros procesos, formando un árbol de procesos. 
- Recursos compartidos 
	 Padres e hijos comparten todos los recursos.
	 Hijo comparte un subconjunto de los recursos del padre. 
	 Padre e hijo no comparten ningún recurso. 
- Ejecución o Padres e hijos ejecutan concurrentemente. 
- Padres esperan hasta que los hijos terminan.

**Ejemplos** 
**UNIX (Linux …)**: la llamada al sistema fork crea un nuevo proceso. 
==las llamadas al sistema fork son costosas==

el fork hace un duplicado exacto del padre, clona el padre pero en un nuevo proceso
![[../Atachments/Pasted image 20250825105732.png]]

sh es una imagen ejecutable

![[../Atachments/Pasted image 20250825105851.png]]

Dando como resultado un arbol de procesos

![[../Atachments/Pasted image 20250826140805.png]]

**Windows**: la API de Windows CreateProcess() crea un nuevo proceso.
### Terminación de procesos

El proceso ejecuta la última sentencia y espera que el SO haga algo (**exit**). 
	- Los datos de salida del hijo se pasan al padre (vía **wait**). 
	- Los recursos de los procesos son liberados por el SO.

El padre puede terminar la ejecución del proceso hijo (**abort**). 
	- El hijo ha excedido los recursos alocados. 
	- La tarea asignada al hijo no es mas requerida.
	- El padre está terminando. 
		1. El SO no permite a los hijos continuar si su padre termina. 
		2. Terminación en cascada.
### Procesos Cooperativos

- Un proceso independiente no puede afectar ni ser afectado por la ejecución de otro proceso. 
-  Un proceso cooperativo puede afectar o ser afectado por la ejecución de otro proceso. 
-  Ventajas de los procesos cooperativos 
	Información compartida 
	Aceleración de la computación
	Modularidad

## Comunicación Interprocesos

Los procesos cooperativos necesitan comunicación interprocesos (IPC)

Se conocen 2 modelos de IPC 
- Memoria compartida 
- Pasaje de Mensajes

![[../Atachments/Pasted image 20250826141015.png]]

### Problema del Productor-Consumidor

En el Paradigma procesos cooperativos, el proceso productor **produce** información que es **consumida** por un proceso consumidor. 
- buffer **ilimitado**, no tiene límites prácticos en el tamaño del buffer. 
- buffer **limitado** supone que hay un tamaño fijo de buffer.

Sistema de mensajes Los procesos se comunican uno con otro sin necesidad de variables compartidas. 

Los IPC proveen dos operaciones: 
- **send**(mensaje) 
- **receive**(mensaje) 
Si P y Q desean comunicarse, necesitan: 
- Establecer un vínculo de comunicación entre ellos 
- Intercambiar mensajes vía send/receive 
Implementación de un vínculo de comunicación 
- lógico (p.e., propiedades lógicas) 
- físico (p.e., memoria compartida, canal hardware)

### Comunicación Directa

 Los procesos deben nombrar al otro explícitamente: 
- **send** (P, mensaje): envía un mensaje al proceso P 
- **receive**(Q, mensaje): recibe un mensaje del proceso Q 
Propiedades del vínculo de comunicación 
- Un vínculo está asociado con exactamente un par de procesos que se comunican. 
- Entre cada par existe exactamente un vínculo. 
- El vínculo puede ser unidireccional, pero es usualmente bidireccional.
### Comunicación Indirecta

Los mensajes son dirigidos y recibidos desde **mailboxes** 
Vínculo de comunicación:
- Se establece solo si los procesos comparten un mailbox común. 
- Puede ser asociado con muchos procesos. 
- Cada par de procesos puede compartir varios vínculos de comunicación. 
- Puede ser unidireccional o bi-direccional. 

Operaciones:
- crear un nuevo mailbox 
- enviar y recibir mensajes por medio del mailbox 
- destruir un mailbox 
Primitivas: 
- **send**(A, message): enviar un mensaje al mailbox A 
- **receive**(A, message): recibir un mensaje del mailbox A
### Sincronización

El pasaje de mensajes puede ser bloqueante o no bloqueante. 
Bloqueante es considerado **sincrónico** 
- Send bloqueante 
- Receive bloqueante 
No bloqueante es considerado **asincrónico** 
- Send no bloqueante 
- Receive no bloqueante

### Buffering

La cola de mensajes asociada al vínculo se puede implementar de tres maneras. 
1. Capacidad: 0 mensajes 
	El enviador debe esperar por el receptor (**rendezvous**).
2. Capacidad limitada: longitud finita de n mensajes El enviador debe esperar si el vínculo está lleno.
3. Capacidad ilimitada – longitud infinita El enviador nunca espera.

## Pipe

Actúa como un conducto que permite que dos procesos se comuniquen

Cuestiones: 
- Comunicación: ¿unidireccional o bidireccional? 
- Comunicación bidireccional, ¿es half o full-duplex? 
- ¿Debe existir una relación (es decir, padre-hijo) entre los procesos de comunicación? 

**Pipe ordinario** "UNIX": no se puede acceder desde fuera del proceso que lo creó. 
Normalmente, un proceso padre crea un pipe y lo usa para comunicarse con un proceso hijo que creó

Son utilizados para comunicaciones unidireccionales 
Permiten la comunicación en el estilo estándar de productor-consumidor 
El productor escribe en un extremo (el final de la tubería) 
El consumidor lee desde el otro extremo (el extremo de lectura de la tubería) 
Requieren una relación padre-hijo entre los procesos de comunicación.

![[../Atachments/Pasted image 20250826142929.png]]

![[../Atachments/Pasted image 20250826142957.png]]

• Para comportamientos predecibles se debe tener un único punto de entrada y un único punto de salida

![[../Atachments/Pasted image 20250826143023.png]]

