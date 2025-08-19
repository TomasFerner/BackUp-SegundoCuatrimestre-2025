# Introducción
## Que es un sistema operativo
Un programa que **actua como intermediario** entre el usuario de una computadora y el hardware de la computadora

Es "El programa que ejecuta todo el tiempo en la computadora" es el **kernel** o **núcleo**, no hay una clara definición de que es, se suele definir mas como lo que hace en si, todo lo demás es un programa de sistema o un programa de aplicación
## Objetivo del sistema operativo
El objetivo del OS es ejecutar los programas de usuario y permitir la solución de problemas del usuario mas fácilmente, uso de hardware de la computadora de manera eficiente
## Componentes del sistema de computo
Hardware <-> sistema operativo <-> programas de aplicación (compiladores, navegadores, kits de desarrollo, etc) <-> Usuario
## Pov Usuario del Os
Interfaz fácil de usar y intuitiva, un uso **personal** anteriormente era brindarle todos los recursos disponibles de la computadora

Los primeros **mainframes** se piensan en las primeras grandes computadoras que utilizaban comandos para responder a la mayoría de usuarios

Las **Workspace** o estaciones de trabajo eran usadas por los usuarios para realizar consultas, luego aparecieron los workspace **moviles** para facilitar su uso, uno de los hitos era mejorar la eficiencia para aumentar la vida util y batería 

Los usuarios también participan en **sistemas embebidos** son sistemas integrados en dispositivos por ejemplo el televisor

## Pov del Sistema Operativo
Alocado de recursos, administra todos los recursos, decide sobre requerimientos conflictivos para asegurar eficiencia y uso imparcial de recursos

Roles del OS: Referi-Ilusionista-Pegamento

## Porque estudiar sistemas operativos
El desarrollo de software parte del desarrollo de un sistema operativo, antes de la implementación de sistemas operativos los usuarios desarrollaban sus propios Os para realizar sus tareas, luego de la creación y estandarización de los sistemas operativos modernos nace la diciplina del Desarrollo de software

## Organización del sistema de computo
Una o varias cpus, ejecución concurrente de CPUs y dispositivos -> compiten por ciclos de memoria
La cpu mueve datos desde/hacia la memoria principal a/desde los buffers locales
La Entrada/Salida es desde el dispositivo al buffer local del controlador
El controlador de dispositivo informa a la cou que ha finalizado su operación por medio de una **interrupción** 

##Interrupciones
Una interrupción transfiere el control a la rutina de servicio de la misma, generalmente por medio del vector de interrupción que contiene las direcciones de todas las rutinas de servicio , el OS es manejado por interrupciones 

Las interrupciones entrantes son des habilitadas mientras otras interrupción esta siendo procesada para prevenir una **perdida de interrupción**

Un **trap** es una interrupción generada por el software causada por un error o por un requerimiento de usuario, es la ocurrencia de una situación por el software que esta ejecutando, los traps son sincronicos porque el usuario los pide

El sistema operativo preserva el estado de la CPU almacenando los
registros y el contador de programa.
Determina que tipo de interrupción ha occurrido:
o polling
o Sistema de interrupción vectoreado
Segmentos de código separados determinan que tipo de acción
deberían llevarse a cabo para cada tipo de interrupción.

### Dos metodos entrada/salida

![[Pasted image 20250818102741.png]]


## Direct memory access (DMA)

Usado por dispositivos de E/S de alta velocidad para transmitir información a velocidades similares a la de la memoria. 

El controlador de dispositivos transfiere bloques de datos desde el buffer de almacenamiento directamente a la memoria principal sin la intervención de la CPU.

Solo una interrupción es generada por bloque, y no una por byte.

![[Pasted image 20250818102954.png]]

## Estructura de almacenaje

**Memoria principal**: único medio de almacenaje que la CPU puede
acceder directamente.

**Almacenaje Secundario**: extensión de la memoria principal que
provee una gran capacidad de almacenaje no volátil.

**Discos Magnéticos**: 
La superficie del disco está logicamente dividida en tracks (pistas), los cuales están subdivididas en sectores. 
El controlador de disco determina la interacción lógica entre el dispositivo y la computadora

## Dispositivos de Almacenaje - Jerarquía

![[Pasted image 20250818103248.png]]

## Arquitectura del Sistema de Cómputo

![[Pasted image 20250818103409.png]]

# Operaciones del Sistema Operativo
## Inicio de la Computadora
El programa de bootstrap es cargado en el encendido o reboot
o Típicamente almacenado en ROM o EEPROM, generalmente conocido como firmware
o Inicializa todos los aspectos del sistema
o Carga el kernel del sistema operativo y comienza la ejecución

## Estructura del Sistema Operativo
La Multiprogramación es necesaria para lograr eficiencia:
o Organiza las tareas (código y datos) de tal manera que la CPU siempre tiene uno ejecutando.
o Un subconjunto del total de tareas en el sistema se mantienen en memoria.
o Una tarea es selecionada y ejecutada vía una planificación de tareas.
o Cuando tiene que esperar (p.e. E/S), el sistema operativo conmuta a otra tarea.

![[Pasted image 20250818103818.png]]


El **Tiempo Compartido (multitarea)** es una extensión lógica en la cual la CPU conmuta tareas tan frecuentemente que los usuarios pueden interactuar con cada tarea mientras está ejecutando, creando la computación **interactiva**.
o El **tiempo de respuesta** debería ser < 1 Segundo.
o Cada usuario tiene al menos un **proceso** ejecutando en memoria.
o Si hay varias tareas listas para ejecutar al mismo tiempo -> **planificación de CPU.**
o Si un proceso no entra en memoria, el swapping lo mueve hacia adentro y hacia afuera de la memoria para ejecutarse.
o La **Memoria Virtual** permite la ejecución de procesos no completos en la memoria

## Operaciones del Sistema Operativo
Los sistemas operativos están controlados por interrupciones, interrupciones son manejadas por el hardware

El error o requerimiento de software crea una **excepción** o **trap**
Por ejemplo: División por cero, requiere por un servicio del sistema operativo
Otros problemas de procesos incluyen lazos infinitos, procesos que se modifican unos con otros o el sistema operativo.

### Interrupción y Trap

![[Pasted image 20250818104432.png]]

La operación en modo dual permite al sistema operativo protegerse sí mismo y otros componentes del sistema
o Modo usuario y modo kernel
o El bit de modo es provisto por el hardware
	o Provee la habilidad para distinguir cuando el sistema está ejecutando código de usuario o código kernel.
	o Algunas instrucciones son privilegiadas, sólo se ejecutan en modo kernel.
Timer para prevenir lazos infinitos / alto consumo de recursos por procesos

### Transición del modo usuario al modo kernel

![[Pasted image 20250818104715.png]]

# Administracion

## Administración de Procesos
Un proceso es un programa en ejecución. Es una unidad de trabajo
dentro del sistema. Un programa es una entidad pasiva, el proceso es
una entidad activa.
El proceso necesita recursos para realizar su tarea.
	o CPU, memoria, E/S, archivos
	o Inicialización de datos

La terminación de procesos require reclamar los recursos reusables.

Los procesos de hilo simple tienen un contador de programa
especificando la locación de la próxima instrucción a ejecutar.
	o El proceso ejecuta instrucciones secuencialmente, una por vez hasta terminar.

Procesos multihilados tienen un contador de programa por hilo. o Típicamente un sistema tiene muchos procesos, algún usuario, algún SO ejecutando concurrentemente en una o más CPUs.
	o Concurrencia por multiplexado de CPUs entre procesos / hilos.

### Actividades
El sistema operativo es responsable por las siguientes actividades en conexión con la administración de procesos.
	o Creación y eliminación de procesos.
	o Suspensión y reactivación de procesos.
	o Provisión de mecanismos para:
		o sincronización de procesos
		o comunicación de procesos
		o manejo de interbloqueos

![[Pasted image 20250818105139.png]]

## Administración de Memoria
Todos los datos antes y después del procesamiento.
Todas las instrucciones en memoria para ejecutar.
Determina que hay en memoria cuando es necesario optimizar la utilización de CPU y el tiempo de respuesta
Actividades de la administración de memoria:
	o Lleva control de que partes de la memoria están siendo usadas y
	por quien.
	o Decide que procesos cargar cuando hay espacio de memoria
	disponible.
	o Ocupa y desocupa espacio de memoria cuando necesite.
### Aministracion de almacenaje
El SO provee una visión lógica y uniforme del almacenaje de
información.
	o Hace abstracción de las propiedades físicas a una unidad lógica de lmacenaje – archivo.
	o Cada medio es controlado por un dispositivo (p.e. disco, cinta, etc).
		o Propiedades variables incluyen velocidad de acceso, capacidad, método de acceso (secuencial o al azar).

#### Aministración del Sistema de Archivos
Los archivos, usualmente están organizados en directorios.
El control de acceso en la mayoría de los sistemas determina quien puede acceder a que.
Las actividades del SO incluyen:
	o Creación y destrucción de archivos y directorios.
	o Soporte de primitivas para el manejo de archivos y directorios.
	o Mapeo de archivos sobre el almacenaje secundario.
	o Respaldo sobre medios de almacenajes estables.
#### Almacenaje Secundario
o Los discos son usados para almacenar datos que no entran en memoria principal o para datos que tienen que ser guardados un largo período de tiempo.
o Su administración es de vital importancia.
o La velocidad de operación de la computadora depende del subsistema de discos y sus algoritmos.
#### Las actividades del SO:
o Administración del espacio libre
o Alocación del almacenaje
o Planificación del disco
#### Caching
Principio importante que es llevado a cabo por varios niveles en una computadora.
La información en uso copiada desde un almacenaje lento a uno más rápido temporariamente.

El almacenaje más rápido (cache) es verificado primero para
determinar si la información está allí:
	o Si está, es usada directamente del cache (rápido)
	o Si no, el dato es copiado al cache y usado allí.
Consideraciones: administración y coherencia
#### Subsistema de E/S

Uno de los propósitos del SO es esconder las peculiaridades de los dispositivos de hardware a los usuarios.
Los subsistemas de E/S son responsables de:
	o Administración de memoria de las E/S incluye:
		**buffering** (almacena datos temporariamente mientras están siendo transferidos),
		**caching** (almacena partes de datos en almacenamiento rápido por rendimiento),
		**spooling** (el solapado de la salida de un job con la entrada a otros)
	o Interfaz general de drivers de dispositivos.
	o Drivers específicos para dispositivos de hardware
# Protección y Seguridad
**Protección**: mecanismo para controlar el acceso de procesos o
usuarios a recursos definido por el SO
**Seguridad**: defensa del sistema contra ataques internos y externos
	o Amplio rango, incluyendo DoS, worms, virus, robo de identidad, robo de servicios
### Ambientes de Computación
Computadora Tradicional
	o Borrosa en el tiempo
	o Ambiente de oficina
	o Redes hogareñas
Computación Distribuida
	o Cliente-Servidor
	o Computación Peer-to-Peer
	o Computación en la nube
Computación Móvil
Sistemas Embebidos de tiempo real
Visualización

### Virtualización
Permite que los sistemas operativos ejecuten aplicaciones dentro de otros sistemas operativos

![[Pasted image 20250818110702.png]]

# Repasar los conceptos sobre:
o interrupciones y dma
o entradas/salidas
o memoria