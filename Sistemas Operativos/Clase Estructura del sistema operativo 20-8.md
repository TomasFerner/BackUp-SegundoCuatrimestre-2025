## Conceptos

Vistas de un OS (3 areas principales del sistema operativo)
	servicios
	componentes e interacciones
	interfaces
### Servicios del Sistema Operativo
Un conjunto de servicios del SO proveen funciones que son útiles al usuario: 
	o Interfaz de Usuario 
	o Ejecución de Programas 
	o Operaciones de E/S 
	o Manipulación del Sistema de Archivos 
	o Comunicaciones 
	o Detección de errors 
	o Y otros: alocación de recursos, contabilidad, protección ..
### Interfaces de usuario del sistema operativo

1.- Interfaz de líneas de comando (Command Line Interface - CLI) o intérprete de comando permite entrar comandos en forma directa, pueden ser por línea de comandos o gráficas: 
	o Algunas veces implementadas en el kernel, otras como programas de sistema 
	o La implementación a veces está embebida, y en otras es invocación a programas.
2.- Interfaz Gráfica (GUI) 
3.- Interfaz Touch (especialmente en móviles)

==no va a preguntar que es un sistema operativo ya que no hay una definición puntual==
## Llamadas al Sistema

Son la interfaz de programación a los servicios provistos por el SO, típicamente escritas en lenguajes de alto nivel (C o C++) 
Mayoritariamente accedidas por programas vía Application Program Interface (API) más que por el uso llamadas a sistema directas

**Métodos para pasar parámetros al SO**

o Parámetros en registros 
o Parámetros almacenados en un bloque, o tabla, en memoria, y la dirección del bloque pasada como parámetro en un registro. 
o Parámetros ubicados o pushed, en una pila (stack) por el programa y popped de la pila por el SO.

![[../Atachments/Pasted image 20250820184157.png]]
### Tipos llamadas al sistema

- control de procesos
- administración de archivos
- administración de dispositivos
- comunicación
- mantenimiento de información
- protección

![[../Atachments/Pasted image 20250820184215.png]]
## Servicios del Sistema

Los programas de sistema proveen un medio conveniente para el desarrollo de programas y ejecución. Pueden ser divididos en: 
	o Manipulación de archivos 
	o Información de estado 
	o Modificación de archivos 
	o Soporte de lenguajes de programación 
	o Carga de programas y ejecución 
	o Comunicaciones 
	o Programas de aplicación 

La visión que tienen la mayoría de los usuarios del sistema operativo está dada por los programas de sistema y no por las llamadas a sistema (system calls).

## Diseño, Implementación y Estructura del Sistema Operativo

### Objetivos de los Usuarios y los objetivos del Sistema
Los objetivos y las especificaciones están influenciados por la elección del hardware, tipo de sistema
**Objetivos de los Usuarios** 
	El SO debe ser conveniente para su uso, fácil de aprender, confiable, seguro y rápido 
**Objetivos del Sistema**
	El SO debería ser fácil de diseñar, implementar y mantener, también flexible, confiable, libre de errores y eficiente
### Diseño e Implementación de un Sistema Operativo
Importante principio de separación 
	**Política**: ¿Qué deberá hacerse? 
	**Mecanismo**: ¿Cómo hacerlo?
 Los mecanismos determinan como hacer algo, las políticas deciden que debe hacerse 
 La separación de política de mecanismo es un principio muy importante, permite máxima flexibilidad si las decisiones políticas son cambiadas más tarde
### Enfoque por Capas

o El sistema operativo está dividido en un número de capas (niveles), cada una construida sobre el tope de otra. La capa inferior (nivel 0), **es el hardware**; la más alta (capa N) es la interfaz de usuario. 
o En forma modular, las capas son seleccionadas de manera que cada una usa funciones (operaciones) y servicios de las capas inferiores.

==ninguno es por capas solo teórico, no se sabe el alcance de cada capa y hasta donde implementarla==

![[../Atachments/Pasted image 20250820184303.png]]

### Estructura de Sistema Microkernel

==Su bajo rendimiento hizo descartar este tipo de arquitectura, en la actualidad se utilza monolítico==
Mueve tanto como se pueda al espacio de usuario 
Las comunicaciones entre módulos de usuarios se realiza por medio de pasajes de mensajes  
**Beneficios**: 
	o Más confiable (menos código corre en el modo kernel) 
	o Más fácil de portar el SO a nuevas arquitecturas 
	o Más fácil de extender 
	o Más seguro 
**Detrimentos**: 
	o Sobrecarga de rendimiento en la comunicación del espacio de usuario al espacio de kernel

![[../Atachments/Pasted image 20250820184318.png]]
### Sistemas Modulados

Los más modernos SOs implementan el kernel en módulos 
	o Usa un enfoque orientado a objetos 
	o Cada componente del núcleo está separado 
	o Los protocolos de comunicación entre ellos son sobre interfaces conocidas 
	o Cada uno es cargado en la medida que sea necesitado dentro del kernel 
En resumen, similar a capas pero más flexible

![[../Atachments/Pasted image 20250820184339.png]]
### Sistemas Híbridos

o Los sistemas operativos modernos no presentan un modelo puro. 
o Los modelos híbridos combinan múltiples aproximaciones para alcanzar rendimento, seguridad, usabilidad.
Cada sistema tiene sus combinaciones de las diferentes propuestas
### Generación y Boot del Sistema

Los sistemas operativos son diseñados para ejecutar sobre diferentes clases de computadora, el sistema debe configurarse para cada computadora específica. 

Programa SYSGEN obtiene información sobre la especificación de hardware al momento de configurar el sistema. 

El SO debe estar disponible al hardware, entonces el hardware puede iniciarlo
o Pequeñas piezas de código – bootstrap loader, localiza el kernel, lo carga en memoria, y lo pone en marcha 
o A veces es un proceso en dos pasos donde el boot block en una locación fija carga el bootstrap loader 
o Cuando se le da energía y se inicializa el sistema, comienza la ejecución a partir de una dirección fija de memoria 
o Firmware es usado para contener el código inicial de boot
### Conceptos de Máquinas Virtuales

¿Porque virtualizamos?
Reduce el costo e incrementa la eficiencia de los existentes recursos de hardware  y lograr más en menos tiempo

Una máquina virtual lleva la propuesta por capas a su conclusión lógica, trata el hardware y el kernel del sistema operativo como si fuera todo hardware. 

Una máquina virtual provee una interfaz idéntica al hardware primitivo subyacente, el sistema operativo crea la ilusión de múltiples procesos, cada uno ejecutando en su propio procesador con su propia memoria (virtual).

Cada invitado es provisto con una copia (virtual) de la computadora.

![[../Atachments/Pasted image 20250820183309.png]]

El Virtual Machine Manager crea, administra y ejecuta las máquinas virtuales. 
**Clasificación** 
	Tipo 0 – son soluciones basados en hardware, que proveen soporte para la creación y administración via el firmware. 
	Tipo 1 – Hypervisors ejecutan directamente sobre el hardware de la máquina. 
	Tipo 2 – Hypervisors ejecutan sobre el sistema operativo host que provee los servicios de virtualización.
