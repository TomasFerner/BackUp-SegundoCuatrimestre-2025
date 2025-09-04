## Conceptos

Un hilo (thread o proceso de peso liviano) es una unidad básica de utilización de CPU, consiste de: o contador de programa 
o conjunto de registros 
o espacio de pila

Todos los hilos de un proceso comparten espacio
### Procesos monohilo y multihilo

![[../Atachments/Pasted image 20250901095908.png]]

Tarea con múltiple hilos: 
- un hilo está bloqueado y esperando, 
- un segundo hilo de la misma tarea puede estar corriendo, 
- un tercer hilo de la misma tarea puede estar listo para ejecutarse. 
- Cooperación de múltiple hilos en una misma tarea: o confiere alto procesamiento total y mejora el rendimiento. 
- facilita el desarrollo de aplicaciones que requieren compartir un buffer común (p.e., productor-consumidor).

### Estados de un hilo

corriendo-listo-espera
### Beneficios

o CAPACIDAD DE RESPUESTA 
o COMPARTIR RECURSOS 
	o Dado que los hilos dentro de un mismo proceso comparten memoria y archivos, pueden comunicarse unos con otros sin invocar al kernel 
o ECONOMÍA 
	o Toma menos tiempo crear un nuevo hilo que un proceso 
	o Menos tiempo terminar un hilo que un proceso 
	o Menos tiempo en conmutar entre dos hilos dentro del mismo proceso 
o UTILIZACIÓN DE ARQUITECTURAS MULTIPROCESADOR 
o ESCALABILIDAD

### Ejemplo Arquitectura de Servidor

![[../Atachments/Pasted image 20250901100315.png]]

### Ejemplo Procesador de texto

![[../Atachments/Pasted image 20250901100422.png]]

### Ejemplos: Procesos Mono y Multihilados

![[../Atachments/Pasted image 20250901100505.png]]

### Programación Multicore

Los sistemas multicore ponen presión sobre los programadores, estos desafíos incluyen:
o Dividir actividades 
o Balance 
o Partición de datos 
o Dependencia de los datos 
o Verificación y depuración

### Ejecución Concurrente y Paralela

![[../Atachments/Pasted image 20250901101008.png]]

### Programación Multicore

Tipos de paralelismo:
	o Paralelismo Datos: distribuye subconjuntos de los mismos datos en varios núcleos, la misma operación en cada uno 
	o Paralelismo Tareas: distribuir hilos (threads) en los núcleos, cada hilo realiza una operación única

![[../Atachments/Pasted image 20250901101213.png]]

## Clasificación de hilos

Nivel de usuario
	- Administración de librería
Nivel Kernel
	- Administración del OS

### Hilos a Nivel de Usuario y a Nivel de Kernel

![[../Atachments/Pasted image 20250901101817.png]]

## Modelos Multihilados

### Muchos a uno

Muchos hilos a nivel de usuario mapean a un hilo a nivel de kernel. o Usado en sistemas que no soportan hilos a nivel kernel.

![[../Pasted image 20250901102038.png]]

### Uno a Uno

Cada hilo nivel usuario mapea a un hilo kernel.

![[../Pasted image 20250901102248.png]]

### Muchos a muchos

Permite que muchos hilos a nivel de usuario mapeen a muchos hilos a nivel de kernel 
Permite al SO crear un número suficiente de hilos a nivel de kernel 

![[../Pasted image 20250901102144.png]]

### Modelado de dos niveles

![[../Pasted image 20250901102318.png]]

## Librerías de Hilos

Las librerías de hilos proveen a los programadores con APIs para crear y administrar hilos 
Dos formas primarias de implementarlas 
	- Librerías enteramente en espacio de usuario 
	- Librería a nivel de Kernel soportada por el SO

### Pools de Hilos

Crea un número de hilos en un pool donde esperan por trabajo 
Ventajas: 
o Usualmente es ligeramente más rápido servir un requerimiento con un hilo existente que crear uno nuevo 
o Permite que el número de hilos de la aplicación sea limitado al tamaño del pool

### Manejo de Signal

Los Signals son usados en UNIX para notificar a un proceso que un evento particular ha ocurrido o Un signal handler es usado para signals a procesos 
1. El Signal es generado por un evento particular 
2. El Signal es enviado a un proceso 
3. El Signal es manejado 

Opciones: 
	o Enviar el signal al hilo sobre el cual el signal se aplica 
	o Enviar el signal a cada hilo en el proceso 
	o Enviar el signal a ciertos hilos en el proceso 
	o Asignar un hilo específico para recibir todos los signals al proceso

### Cancelación de Hilos

Terminar un hilo antes que finalice 
Dos propuestas generales: 
	o Cancelación asincrónica termina el hilo señalado inmediatamente 
	o Cancelación Diferida permite al hilo señalado verificar periódicamente si debería ser cancelado

## Hilos en Linux

Linux se refiere a ellos como tareas más que como hilos

La creación de hilos es hecha por la llamada a sistema clone() o clone() .permite a una tarea hija compartir el espacio de direcciones de la tarea-padre (proceso)