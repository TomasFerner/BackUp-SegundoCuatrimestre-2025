# Problemas: Conceptos Generales
Temas Necesarios:
	[[Clase Introduccion a la Materia 18-8]]
	[[Clase Estructura del sistema operativo 20-8]]
## 1. ¿Cuales son las dos funciones principales de un Sistema Operativo?

Las 2 funciones principales del sistema operativo son:

Ejecutar los programas del usuario y permitir la solución de problemas del usuario mas fácilmente, utilizando el hardware de manera eficiente y haciendo un uso conveniente del sistema de la computadora, decide sobre los requerimientos conflictivos para asegurar la eficiencia y el uso imparcial de los recursos disponibles

Se utiliza como programa de control supervisando la ejecución de los programas, evitando errores y usos indebidos del hardware de la computadora
## 2. Cite varios SO que conozca. ¿Puede clasificarlos de alguna manera? ¿Cuales son los diferentes criterios que utilizaría para la clasificación de los SO?

Sistemas operativos que conozco: Windows, MacOS, Linux, android, Unix, Director

Se podrían clasificar por propósito:
	de propósito general (Windows, Linux)
	de tiempo real (VxWorks, QNX)
	embebidos (Android en TV, iOS en iPhone)
Tambien se podrían clasificar por el tipo de interfaz:
	de línea de comandos (Unix)
	gráficas (Windows, macOS)
## 3. Para cada una de las siguientes aseveraciones, indique si son verdaderas o falsas. Justifique su respuesta 

### a) Las computadoras personales se pueden utilizar sin sistema operativo. 

**Verdadero**, pero muy limitado: solo podrían ejecutar firmware o un programa específico cargado en memoria (ej. BIOS o sistemas embebidos). Sin OS no habría entorno general de ejecución.

En una PC, el firmware es un tipo de software incrustado en el hardware que actúa como un puente entre el sistema operativo y los componentes físicos de la computadora. Básicamente, es un programa de bajo nivel que permite que el hardware funcione correctamente, incluyendo el proceso de arranque y la comunicación con otros dispositivos.

**Tipos comunes:**
- **Bios (Basic Input/Output System):** Un tipo de firmware que se encuentra en la placa base y gestiona el proceso de arranque y la inicialización del hardware. 
- **UEFI** Un reemplazo más moderno de la BIOS, que ofrece mayor flexibilidad y seguridad.
### b) Los sistemas operativos son dependientes de la arquitectura de la computadora.

**Verdadero**, porque un OS debe estar diseñado para las instrucciones, registros y mecanismos de interrupción de la arquitectura (ej. un OS para x86 no funciona en ARM sin adaptación).

Una interrupción es una solicitud enviada al procesador para que pause su actividad actual y ejecute una **rutina de servicio de interrupción (ISR)**. Estas señales pueden ser generadas por hardware (dispositivos externos) o software (programas)

Tipos de Interrupciones
**Interrupciones de Hardware**
    Originadas por dispositivos físicos (ej: teclado, disco duro, tarjeta de red).
    Ejemplo: Al presionar una tecla, el controlador del teclado envía una interrupción al procesador.
**Interrupciones de Software (Trap o Excepción)**:
    Generadas por programas o el propio OS mediante instrucciones (ej: `int 0x80` en Linux para llamadas al sistema).
    Incluyen excepciones por errores (división por cero, acceso inválido a memoria)
### c) Todas las computadoras utilizan sistemas operativos.

**Falso**, algunos sistemas embebidos o microcontroladores ejecutan programas directamente sin SO, solo firmware básico

## 4. ¿De que manera el usuario utiliza, directamente o indirectamente el sistema operativo?

- **Directamente:** mediante comandos, llamadas al sistema (ej. abrir un archivo con `open`, comandos dentro de un terminal).
- **Indirectamente:** a través de aplicaciones que usan servicios del OS (ej. un navegador que pide al OS acceso a la red o al disco).
## 5. Ejemplo de dos objetivos de diseño que pueden contradecirse.

Seguridad y Eficiencia,  si bien no son excluyentes, centrarse solamente en la eficiencia puede no otogar la robustes necesaria para alcanzar la seguridad y de manera inversa alcanzar altas capas de proteccion o robustes puede implicar una penalización en la eficiencia

Rendimiento y bajos costo, obtener mayor rendimiento suele estar asociado a aumentar el presupuesto y los costos de la fabricación del hardware y software, esto ya que el hardware especifico altamente eficiente suele ser mas caro además la optimización de procesos en programas también implica un mayor gasto tanto por mano de obra como recursos asignados
## 6. Se ha insistido en la necesidad de que un sistema operativo haga uso eficiente de los recursos. ¿Cuando es apropiado que un sistema operativo deje de lado este principio y consuma recursos? ¿Por que estos sistemas operativos son igualmente utilizados? 

Si el software se centra en la comodidad del usuario y la facilidad de uso, estas caracteristicas podrían implicar un uso ineficiente de los recursos

**Windows o macOS** gastan recursos en interfaces gráficas, animaciones o asistentes, lo que no es “eficiente” pero mejora la experiencia del usuario, estos OS son igualmente usados porque privilegian la **interacción amigable** y la **productividad**, no solo la eficiencia técnica
## 7. Considerando las diferentes definiciones (funcionalidades/objetivos) de sistemas operativos. Considere si el sistema operativo debe incluir aplicaciones tales como navegadores (browsers), programas de correo electrónico. Discuta pros y contras sobre la inclusion de este tipo de aplicaciones.

La necesidad de Inclusion de este tipo de **aplicaciones** y **programas** depende totalmente del usuario, mientras que algunos querrán que navegadores y servicios de correo esten incluidos, otros querran tener una computadora lo mas limpia o con menos agregados posibles
**Pros:**
    - Facilita al usuario un entorno completo desde el inicio.
    - Integración más fluida entre OS y aplicaciones.
    - Ejemplo: Windows con Edge, Android con Gmail.
**Contras:**
    - Aumenta la complejidad y tamaño del OS.
    - Menor flexibilidad: el usuario recibe software impuesto.
    - Riesgos de monopolio y menos modularidad (caso Windows + IE).
## 8. Es posible escribir un SO en un lenguaje de alto nivel, que ventajas y desventajas tendría. 
Si es posible escribir un OS en un lenguaje de alto nivel
**Ventajas:**
    - Mayor portabilidad (menos dependiente del hardware).
    - Código más legible y fácil de mantener.
    - Desarrollo más rápido.
**Desventajas:**
    - Menor control directo del hardware (latencia, registros).
    - Posible pérdida de eficiencia frente al uso de ensamblador o C.  
    Unix y Linux están escritos principalmente en **C**, un lenguaje de nivel medio pero no puede considerar de bajo nivel respecto a la definición purista, un lenguaje de bajo nivel puede ser el lenguaje ensamblador

## 9. Defina las propiedades esenciales de los siguientes tipos de sistemas operativos: 
### a) batch
- Procesan trabajos en grupo sin interacción directa con el usuario.
- Maximiza uso de CPU, pero tiempo de respuesta largo
### b) interactivo, 
- Permite comunicación directa usuario–máquina (ej. shell, interfaz gráfica).
- Prioriza la respuesta rápida.
### c) tiempo compartido (multitarea)
- Conmuta entre múltiples procesos de usuarios.
- Busca **interactividad** dando la ilusión de ejecución simultánea.
- Respuesta < 1s para el usuario
### d) tiempo real. 
- Responde en un tiempo máximo garantizado.
- Usado en control de procesos industriales, embebidos, robótica.
- La **puntualidad** es más importante que la eficiencia.
## 10. Enumere y explique las características a tener en cuenta en multiprogramación. ¿Que relación hay entre multiprogramación y tiempo compartido? ¿Existen diferencias con tiempo compartido?

- Planificación de CPU (qué proceso ejecutar).
- Manejo de memoria (qué procesos caben en memoria).
- Manejo de Entradas/Salidas (para evitar CPU ociosa).
- Protección y aislamiento entre procesos.

**Relación con tiempo compartido:**
La **multiprogramación** busca maximizar uso de CPU ejecutando varios procesos en memoria.
El **tiempo compartido** es un paso más: usa la multiprogramación + planificación rápida para **garantizar respuesta interactiva** al usuario.  
Por lo tanto la diferencia clave radica en que:
- Multiprogramación = **eficiencia**.
- Tiempo compartido = **interactividad y respuesta rápida**
## 11. En entornos de multiprogramacion y tiempo compartido, los usuarios comparten el sistema simultáneamente. Esta situacion puede resultar en varios problemas de seguridad. ¿Cuales son estos problemas? ¿Es posible garantizar el mismo grado de seguridad en una maquina de tiempo compartido como se tiene en una maquina dedicada? 

- **Acceso indebido a memoria** de otros procesos.
- **Interferencia en ejecución** (modificación o detención de procesos ajenos).
- **Robo de información** (claves, datos privados) aprovechando mecanismos accesibles por multiprogramación y tiempo compartido.
- **Denegación de servicio** (un usuario acapara CPU o E/S).

No se puede garantizar **el mismo nivel de seguridad que en una máquina dedicada**, porque en tiempo compartido existen múltiples usuarios concurrentes. Sin embargo, mecanismos como **protección de memoria, privilegios de usuario/kernel y control de acceso** permiten un nivel de seguridad aceptable.
## 12. Describa las diferencias entre multiprocesamiento simétrico y asimétrico. ¿Cuales son las ventajas y desventajas de un sistema con multiprocesadores? 

SMP (Simétrico):
    - Todos los procesadores son iguales.
    - Comparten la memoria y pueden ejecutar cualquier tarea.
    **Ventaja:** mejor balance de carga.
    **Desventaja:** mayor complejidad de coordinación.
AMP (Asimétrico):
    - Un procesador maestro controla y asigna trabajo a procesadores esclavos.
    **Ventaja:** más simple de implementar.
    **Desventaja:** cuello de botella en el procesador maestro
## 13. ¿Cual es la diferencia entre una interrupción y un trap? ¿Cual es el uso de cada una? 

- Una **interrupción** transfiere el control a la rutina de servicio de la misma, generalmente por medio del vector de interrupción, que contiene las direcciones de todas las rutinas de servicio.
- Las **interrupciones** entrantes son deshabilitadas mientras otra interrupción está siendo procesada para prevenir una pérdida de interrupción. 
- Un **trap** es una interrupción generada por el software causada por un error o por un requerimiento de usuario.

## 14. ¿Porque es necesaria la operación en “modo dual”? 

Porque permite **distinguir entre ejecución de usuario y ejecución del kernel**, asegurando que:
- El OS se proteja de accesos indebidos de procesos de usuario.
- Solo el kernel ejecute instrucciones privilegiadas (ej. manejo de memoria, E/S, interrupciones).  

Sin modo dual, un proceso podría corromper el sistema completo.
## 15. ¿Como determina el sistema en que modo se encuentra?

Mediante un **bit de modo** provisto por el hardware:
- **Bit = 1 → modo usuario** (ejecución de programas de usuario, sin acceso a instrucciones privilegiadas).
- **Bit = 0 → modo kernel** (ejecución de OS, con acceso total).  
El cambio ocurre en interrupciones, traps o llamadas al sistema, y vuelve a usuario al finalizar

## 16. ¿Cual es el propósito de los systems calls? 

Son la **interfaz entre los programas de usuario y el sistema operativo**.  
Permiten que una aplicación solicite servicios al OS (manejo de archivos, procesos, E/S, memoria) de forma **segura y controlada**, en vez de acceder directamente al hardware

## 17. ¿Porque es necesario que el hardware ofrezca mecanismos de protección de I/0, de memoria y de la CPU? Explique como se realiza dicha protección. 

- **Memoria:** evita que un proceso acceda o modifique la memoria de otro o del OS. Se protege con registros de base y límite o MMU(Memory manager unit).
- **CPU:** impide que un proceso acapare la CPU (uso de _timer_ para forzar cambio de contexto).
- **Input/Output:** asegura que solo el kernel ejecute operaciones de entrada/salida, mediante instrucciones privilegiadas.  

Sin estos mecanismos, un proceso malicioso o con errores podría bloquear o corromper todo el sistema.

## 18. Cuales de las siguientes instrucciones deben ser privilegiadas: 

### a) Fijar (set) el valor de un timer 
Privilegiada (evita que un usuario anule la planificación).
### b) Leer el reloj 
No privilegiada (segura, solo lectura).
### c) Borrar la memoria 
Privilegiada (riesgo de corromper OS o procesos).
### d) Deshabilitar las interrupciones 
Privilegiada (un usuario podría bloquear al sistema).
### e) Cambiar a modo usuario
Privilegiada (controlado por kernel)
### f) Cambiar a modo monitor 
Privilegiada (un usuario no puede entrar al kernel libremente).
### g) Leer una pista/sector de un disco magnético 
Privilegiada (puede comprometer datos de otros usuarios).
## 19. ¿Es posible construir un OS seguro cuando el hardware no provee operación en modo dual? 

Por lo general **no**, porque sin modo dual no hay forma de restringir que el usuario ejecute instrucciones críticas.  
Se podrían usar mecanismos alternativos (firmware protegido, emuladores, microcódigo), pero serían poco eficientes y fáciles de vulnerar.
En definitiva construir un OS seguro en su totalidad es una tarea imposible incluso restringiendo operación en modo dual
## 20. Algunos sistemas de computo antiguos protegían al S.O. alojándolo en una partición de memoria especial, donde no podıa ser modificada por ninguna tarea de un usuario, ni tampoco por el mismo S.O. ¿Que dificultades tiene este esquema?

- El OS no podría **modificarse a sí mismo** (actualizaciones dinámicas, carga de drivers).
- Limita la **flexibilidad**: el OS moderno necesita administrar dinámicamente memoria y procesos, además de gestionar actualizaciones criticas necesarias por vulnerabilidades descubiertas
- No impide accesos indebidos a **otros recursos** (CPU, Entradas/Salidas).  
Es un método rígido y parcial, superado por el esquema de **modo dual + protección por hardware**

## 21. A continuación se detalla una lista de operaciones que normalmente son protegidas. Indique el conjunto mínimo que deben protegerse. 
### a) leer del area de memoria del monitor 
 proteger (evita que un usuario acceda al código del SO).
### b) escribir en el area de memoria del monitor 
proteger (impide corrupción del SO).
### c) obtener (fetch) una instrucción del area de memoria del monitor 
no necesario, el fetch solo ejecuta instrucciones legítimas del kernel cuando ya está en modo privilegiado.
### d) ejecutar un trap 
no se protege, al contrario: es el mecanismo para entrar al kernel de manera controlada.
### e) acceder al area de I/O (lectura o escritura). Sistemas Operativos 3 22. ¿Cual es el propósito del interprete de comandos? ¿Por que usualmente esta separado del kernel? 
proteger, porque un usuario no puede manipular dispositivos directamente

**Conjunto mínimo protegido:** **a, b, e**.

## 22. ¿Cual es el propósito del interprete de comandos? ¿Por que usualmente esta separado del kernel?

Provee la **interfaz entre el usuario y el sistema operativo**: recibe órdenes (ej. crear procesos, abrir archivos) y las traduce en _system calls_.
Está separado del kernel porque:
    No es esencial para la gestión del hardware.
    Permite flexibilidad (diferentes shells o interfaces gráficas).
    Si falla, no compromete al núcleo del sistema
## 23. ¿Cual es la principal ventaja de usar un microkernel en el diseño de sistemas? ¿Como interactúan los programas de usuario y los servicios del sistema en una arquitectura basada en microkernel? ¿Cuales son las desventajas de usar la arquitectura de microkernel? 

**Ventajas:**
    - Más seguro y estable: menos código en el kernel → menor riesgo de fallos.
    - Fácil de extender y portar: servicios se implementan en espacio de usuario.
**Desventajas:**
    - Comunicación por mensajes introduce **overhead** (más lento que llamadas directas en un kernel monolítico)

La interacción se modela de la siguiente manera: programas de usuario ↔ microkernel ↔ servidores de sistema (archivos, memoria, drivers) mediante **paso de mensajes**.

## 24. ¿En que se asemejan la arquitectura kernel modular y la arquitectura en niveles? ¿En que se diferencian? 

- **Semejanza:** ambos buscan **organización estructurada** y **separación de funciones**.
- **Diferencia:**
    - **Arquitectura en niveles:** jerárquica y rígida, cada nivel solo interactúa con el inmediatamente inferior/superior.
    - **Kernel modular:** más flexible, permite **cargar o descargar módulos dinámicamente** (ej. drivers en Linux).

## 25. ¿Cual es la ventaja para un diseñador de sistemas operativos la utilización de una maquina virtual? ¿y para un usuario?

- **Para el diseñador del SO:**
    - Permite experimentar, depurar y probar SO sin comprometer la máquina real.
    - Aísla fallos y facilita investigación.
- **Para el usuario:**
    - Ejecutar múltiples SO en la misma máquina.
    - Aislamiento de aplicaciones (seguridad).
    - Portabilidad (ej. usar Windows y Linux en un mismo hardware). 