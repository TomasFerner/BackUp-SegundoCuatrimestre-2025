Libro: [[Operating_systems__principles_and_practice (Anderson og Dahlin).pdf]]
# Introducción

> [!PDF|red] [[Sistemas Operativos/Operating_systems__principles_and_practice (Anderson og Dahlin).pdf#page=25&selection=42,1,57,10&color=red|Operating_systems__principles_and_practice (Anderson og Dahlin), p.25]].
> 
> 
 Se define al Sistema Operativo como el **software que maneja los recursos de la computadora**,


 > [!PDF|note] [[Sistemas Operativos/Operating_systems__principles_and_practice (Anderson og Dahlin).pdf#page=26&selection=74,5,130,7&color=note|Operating_systems__principles_and_practice (Anderson og Dahlin), p.26]]
> 
> ![[../Atachments/{5A529406-50AB-4AD7-AA0A-8D3D415E23EB}.png]]
 Imagen que muestra como funciona un web servers, la maquina del cliente envía una petición HTTP GET al web server, el servidor decodifica el paquete, lee al archivo y envía el contenido de nuevo al cliente


La idea principal de estudiar los conceptos del libro es que entender como funciona un sistema operativo permite utilizar el conocimiento aprendido para la implementación portable, eficiente y efectivo de todo tipo de software especifico como navegadores, juegos, interfaces graficas, bases de datos, etc.

> [!PDF|violet] [[Sistemas Operativos/Operating_systems__principles_and_practice (Anderson og Dahlin).pdf#page=26&selection=441,0,462,8&color=violet|Operating_systems__principles_and_practice (Anderson og Dahlin), p.26]]
> Uno de los objetivos del sistema operativo es facilitar el desarollo de aplicaciones

> [!PDF|red] [[Sistemas Operativos/Operating_systems__principles_and_practice (Anderson og Dahlin).pdf#page=27&selection=55,5,101,5&color=red|Operating_systems__principles_and_practice (Anderson og Dahlin), p.27]]
> > Multitarea: manejar multiples peticiones al mismo tiempo


## 1.1 Que es un sistema Operativo

> [!PDF|green] [[Sistemas Operativos/Operating_systems__principles_and_practice (Anderson og Dahlin).pdf#page=28&selection=141,0,173,1&color=green|Operating_systems__principles_and_practice (Anderson og Dahlin), p.28]]
>Un Sistema operativo es una capa de software que maneja los recursos de la computadora para el usuario y sus aplicaciones

> [!PDF|blue] [[Sistemas Operativos/Operating_systems__principles_and_practice (Anderson og Dahlin).pdf#page=28&selection=598,0,647,1&color=blue|Operating_systems__principles_and_practice (Anderson og Dahlin), p.28]]
> ![[../Atachments/{6A14797B-C702-4E83-8C51-93CCA4841553} 1.png]]
> El usuario interactúa con las aplicaciones, las aplicaciones se ejecutan en un entorno provisto por el sistema operativo, el sistema operativo funciona como mediador para el acceso al hardware 

### Como un sistema operativo puede correr multiples aplicaciones?

Los sistemas operativos tienen que poder cumplir 3 roles:

> [!PDF|light blue] [[Sistemas Operativos/Operating_systems__principles_and_practice (Anderson og Dahlin).pdf#page=29&selection=83,0,178,5&color=light blue|Operating_systems__principles_and_practice (Anderson og Dahlin), p.29]]
> Ser el **Arbitro** de la maquina
> - Los sistemas operativos manejan los recursos compartidos entre las diferentes aplicaciones corriendo en la misma maquina física
> - Los sistemas operativos pueden aislar aplicaciones de otras aplicaciones, para que un bug en una no corrompa otra aplicación corriente en la misma maquina
> - Adema los sistemas operativos tienen que protegerse a si mismo por virus maliciosos
> - Como las aplicaciones comparten los mismos recursos físicos, el sistema operativo debe decidir que aplicaciones reciben recursos y en que momento los reciben

> [!PDF|red] [[Sistemas Operativos/Operating_systems__principles_and_practice (Anderson og Dahlin).pdf#page=29&selection=180,0,332,12&color=red|Operating_systems__principles_and_practice (Anderson og Dahlin), p.29]]
>Ser el **Ilusionista o mago** de la maquina
>- Los sistemas operativos proveen un mecanismo de abstracción del hardware para simplificar el diseño de aplicaciones, los sistemas operativos dan la illusion de tener memoria casi infinita, además de que el usuario sienta que cada programa tenga la totalidad de la computadora disponible para el mismo
>- Dado que las aplicaciones están escritas en un nivel de abstraccion mayor, los sistemas operativos pueden cambiar osas de manera imperceptible la cantidad de recursos asignados a cada tarea
> 

> [!PDF|violet] [[Sistemas Operativos/Operating_systems__principles_and_practice (Anderson og Dahlin).pdf#page=29&selection=335,0,349,10&color=violet|Operating_systems__principles_and_practice (Anderson og Dahlin), p.29]]
> Ser el **pegamento** de la maquina
> - Los sistemas operativos proveen un set de servicios communes que facilitan la comunicacion entre aplicaciones, como resultado copiar y pegar trabajo de manera uniforme a traves del sistema, coomo resultado un archivo escrito por una aplicacion puede ser leido por otra aplicacion
> - Varios sistemas operativos proveen una interfaz de usuario común de rutinas que permite que las aplicaciones tengan un formato y sensación similar 
> - Una de las características mas importantes del sistema operativo es la capacidad de separar la ejecución de aplicaciones de los imputs/outputs (I/O) de los dispositivos interactuando con el, esto para que las aplicaciones puedan ser escritas independientemente del tipo de dispositivo q interactua con la computadora (diferentes modelos y marcas de teclado por ejemplo)

Esta figura muestra la estructura general de un sistema operativo, de manera mas extensa, dividido por sus distintas capas de abstraccion

![[../Atachments/{61CDFCDE-6FC1-4A90-9B29-E09C07801FD5}.png]]

### Compartir Recursos: El sistema operativo como un arbitro

El sistema operativo tiene que ser capaz de permitir que las aplicaciones compartan información entre ellas al mismo tiempo que aísla las mismas para conservar la integridad del sistema, ser capaz de ejecutar actividades cuando otras se frenan e incluso ejecutar mismos procesos en paralelo 

Compartir recursos genera desafíos a superar:
#### La localización de recursos
> [!PDF|brown] [[Sistemas Operativos/Operating_systems__principles_and_practice (Anderson og Dahlin).pdf#page=31&selection=572,1,680,1&color=brown|Operating_systems__principles_and_practice (Anderson og Dahlin), p.31]]
> Los sistemas operativos deben ser capaces de correr todas las actividades y procesos de manera simultanea y separada, asignado recursos a cada uno de manera apropiada, impidiendo que un loop que se ejecute en la totalidad del hardware bircke la computadora por la incorrecta asignacion de recursos

#### El aislamiento

> [!PDF|violet] [[Sistemas Operativos/Operating_systems__principles_and_practice (Anderson og Dahlin).pdf#page=32&selection=124,0,303,11&color=violet|Operating_systems__principles_and_practice (Anderson og Dahlin), p.32]]
> Un error en una aplicación no debe romper otra aplicación o incluso el sistema operativo mismo, este concepto se llama **aislamiento fallido**, encontrar errores seria infinitamente mas complicado si una aplicación podría corromper estructuras de datos de otras aplicaciones 

#### La comunicación

> [!PDF|green] [[Sistemas Operativos/Operating_systems__principles_and_practice (Anderson og Dahlin).pdf#page=32&selection=448,0,597,7&color=green|Operating_systems__principles_and_practice (Anderson og Dahlin), p.32]]
>La contrapartida del aislamiento, los sistemas operativos deben poder comunicarse con las diferentes aplicaciones y diferentes usuarios, ademas de permitir que las aplicaciones trabajen conjuntamente para garantizar un funcionamiento correcto e integro del sistema

### Enmascarando limitaciones: El sistema operativo como ilusionista

Un Sistema operativo permite enmascarar los recursos del sistema a los diferentes procesos que suceden en la computadora, permitiendo que aplicaciones  tengan asignados diferentes recursos en cada momento incluso corriendo en el mismo hardware

> [!PDF|light blue] [[Sistemas Operativos/Operating_systems__principles_and_practice (Anderson og Dahlin).pdf#page=33&selection=348,0,434,9&color=light blue|Operating_systems__principles_and_practice (Anderson og Dahlin), p.33]]
> La **virtualización** permite que las aplicación tengan la illusion de tener recursos que no están físicamente disponible, por ejemplo un sistema operativo puede permitir la abstraction de que cada aplicación tiene sus propios procesadores, incluso si a nivel de hardware hay solo 1 disponible 

Una **maquina virtual** consiste en que un sistema operativo se virtualiza totalmente, ejecutándose como una aplicación encima de otro sistema operativo, el sistema operativo virtualizado se le dice **guest OS o invitado OS**, una de las ventajas de la maquina virtual es la compatibilidad, de tal manera que si el programa solo corre en una version mas antigua del sistema este puede funcionar en un sistema mas nuevo virtualizando el anterior

![[../Atachments/{57EC5825-81C9-4A22-912F-66A829202D86}.png]]


### Proveedor de servicios comunes: El sistema operativo como pegamento

> [!PDF|violet] [[Sistemas Operativos/Operating_systems__principles_and_practice (Anderson og Dahlin).pdf#page=34&selection=163,0,178,7&color=violet|Operating_systems__principles_and_practice (Anderson og Dahlin), p.34]]
> Los sistemas operativos tienen que proveer un set comunes, estandarizado de servicios a las aplicaciones para simplificar y estandarizar los diseños

Este concepto esta altamente relacionado con **compartir recursos**, una de las razones por los que los sistemas operativos proveen servicios comunes es para facilitar la comunicación entre aplicaciones 

En vez de permitir que cada aplicación tenga sus propios servicios y métodos se provee servicios comunes, mejorando la compatibilidad y extensibilidad

**La mayor parte de el código de los sistemas operativos se centra en proveer estos servicios comunes** y la capacidad de un sistema operativo en cumplir este requisito radica en que tan bien se manejan los otros 2, **arbitraje y ilusionista**

### Patrones de diseño en un Sistema Operativo

**Cloud computing** es un modelo de computación donde las aplicaciones corren en una infraestructura de ejecución y almacenamiento en larga escala en vez de en la computadora del propio usuario

Este modelo se enfrenta a los mismos problemas que los sistemas operativos, como podemos hacer para hacer una administración eficiente de los recursos que nos provee el hardware(**arbitro**), como podemos aislar los cambios que proveen los usuario de los cambios realizado en el hardware ubicado en la infraestructura(**Ilusionista**), dado que los servicios cloud se distribuyen a varias maquinas diversas, que abstracción podríamos proveer para ayudar a los servicios a coordinar y compartir información a traves de las diversas actividades(**pegamento**)

![[../{5BB23A75-A6CA-4130-A759-D62183C4EF13}.png]]

## 1.2 Evaluación de los sistemas operativos

El libro menciona diferentes temas o criterios para la implementación de u sistema operativo

> [!PDF|red] [[Sistemas Operativos/Operating_systems__principles_and_practice (Anderson og Dahlin).pdf#page=41&selection=83,0,195,7&color=red|Operating_systems__principles_and_practice (Anderson og Dahlin), p.41]]
> - Fiabilidad y disponibilidad: El sistema operativo hace lo que queremos, la disponibilidad hace referencia es al porcentaje de tiempo que el sistema esta disponible y usable
>    Los 2 factores principales que afectan la disponibilidad: la frecuencia de fallos y el tiempo que le toma al sistema en retomar un estado usable
> - Security: puede el sistema operativo ser vulnerado, se habla de la importancia en el aislamiento de procesos para prevenir esto, sin dejar al sistema en un estado donde ninguna comunicacion este permitida dejandolo inutil a compartir datos
> - Portabilidad: es el sistema operativo fácil de mover entre las diferentes plataformas y hardware
> - Rendimiento: es la interfaz compatible con las diferentes resoluciones, o es invasivo al usuario, se mencionan métricas como el overhead y la eficiencia, through put y predictability
> - Adopcion: cuantos usuarios están por este sistema operativo

Muchos de estos criterios se contradicen entre si, por ejemplo aumentar la portabilidad puede impactar negativamente en la seguridad del sistema operativo, estas contradicciones se les llama **trades offs**


## 1.3 Sistemas Operativos: pasado, presente y futuro.

Se habla de como el autor cree que los principios de los sistemas operativos actuales persistirán incluso con cambios radicales en software y hardware, se menciona la ley de Moore y la reducción en los costos incluso mejorando las prestaciones
### Los primeros sistemas operativos

> [!PDF|green] [[Sistemas Operativos/Operating_systems__principles_and_practice (Anderson og Dahlin).pdf#page=49&selection=532,0,771,6&color=green|Operating_systems__principles_and_practice (Anderson og Dahlin), p.49]]
> >Los primeros sistemas operativos eran librerías en ejecución destinadas a simplificar la programación de las primeras computadoras, los primeros sistemas operativos nacieron por la necesidad de reducir los errores de los programas de los usuarios brindándoles servicios comunes con los que interactuar, por ejemplo brindaban una estandarización de las rutinas de inputs/outputs  para que cada usuario pudiera vincularlo a su programa, estos servicios aumentaban la probabilidad de que el programa ejecutado por el usuario produzca un output util

### Sistemas operativos Multi-Usuario 

El **Sistema Operativo Batch** es un tipo de sistema operativo en el que los programas (llamados _jobs_) se agrupan en lotes y se ejecutan de manera secuencial sin intervención del usuario durante la ejecución. El sistema se encarga de cargar un trabajo, ejecutarlo y luego descargarlo

Su objetivo principal es maximizar el uso de la CPU en entornos donde los dispositivos de I/O eran muy lentos.

El siguiente paso fue **compartir**, introduciendo así ventajas y nuevos desafíos

La CPU cargaba un programa, lo ejecutaba y después lo descargaba. El problema era que la **CPU quedaba ociosa** cada vez que el sistema tenía que hacer operaciones de **entrada/salida (I/O)**, porque leer desde disco o cinta magnética era muchísimo más lento que ejecutar instrucciones.

Ahí es donde entra el **DMA (Direct Memory Access)** que permitía acceder a la memoria del sistema para leer o escribir independientemente de la CPU:

- **Sin DMA:** cada vez que había que leer o escribir datos, la CPU tenía que ir “manejando” la transferencia byte a byte o palabra a palabra. Eso la bloqueaba durante mucho tiempo.
- **Con DMA:** el sistema operativo podía **programar el controlador de DMA**, indicándole:
    - la dirección de memoria donde poner los datos,
    - la cantidad de datos,
    - y el dispositivo de origen/destino.

Después, el **controlador de DMA** se encargaba de mover los datos directamente entre la memoria y el dispositivo **sin intervención constante de la CPU**.

Esto fue clave para los sistemas batch porque:

1. **Permitió overlap (superposición):** mientras un trabajo estaba corriendo en la CPU, en paralelo se podían ir transfiriendo datos de entrada/salida del siguiente trabajo.
2. **Evitó que la CPU quedara idle:** ya no tenía que esperar a que un dispositivo lento terminara, podía seguir ejecutando instrucciones.
3. **Introdujo el concepto de interrupciones:** cuando el DMA finalizaba, avisaba al procesador mediante una **interrupción**. Ahí el SO retomaba el control para continuar con la siguiente tarea o programar otro DMA.

Luego vino la **multiprogramación** (varios programas en memoria, CPU casi siempre ocupada), lo que llevó a problemas de aislamiento,  que se resolvieron con protección de memoria. La dificultad de probar sistemas operativos directamente en el hardware impulsó el desarrollo de las **máquinas virtuales**, que hoy son clave tanto para desarrollo como para compatibilidad.

Una **VM** permite ejecutar un SO como si fuera una aplicación, sobre un **monitor de máquinas virtuales** (hoy llamado hipervisor).

El SO de prueba cree que controla el hardware real, pero en realidad corre sobre una **abstracción (AVM)** idéntica a la máquina física.

Esto facilita:
- Desarrollo y prueba de SO sin interrumpir el sistema real.
- **Compatibilidad hacia atrás** (ejecutar apps viejas junto con las nuevas).
- **Soporte multiplataforma** (ej. correr Windows o Linux dentro de macOS).

### Sistemas operativos de tiempo compartido

Un **Sistema Operativo de Tiempo Compartido** esta diseñado para la **interacción directa con el usuario**. Cada acción de entrada (tecla, clic, movimiento del mouse) genera una **interrupción** que el sistema operativo captura y encola. Luego, la aplicación correspondiente procesa el evento en una **ráfaga muy corta de actividad**, actualizando la salida en pantalla antes de esperar el próximo evento. Este modelo requiere que tanto el sistema como las aplicaciones estén preparados para manejar **cientos o miles de eventos por segundo**, en contraste con los sistemas batch que se orientan a la ejecución continua de largas tareas sin intervención del usuario.

Con la disminución de costos gracias a la Ley de Moore, las computadoras dejaron de enfocarse solo en aprovechar la CPU y comenzaron a diseñarse para el **uso interactivo**. En los años setenta apareció **UNIX**, base de sistemas como MacOS, Linux, Android y VMware. 

Esto dio paso a los **sistemas de tiempo compartido**, donde cada acción del usuario genera interrupciones que el sistema operativo procesa en ráfagas muy cortas, permitiendo una experiencia interactiva fluida. 

Un modelo similar se aplica en los **servidores web**, que dependen de DMA e interrupciones para atender gran cantidad de peticiones breves. Más tarde, con la llegada de las **computadoras personales**, cada usuario pudo tener su propia máquina, lo que consolidó el modelo **cliente-servidor**, centrado en el acceso a datos compartidos.

### Sistemas operativos modernos

Se habla de los sistemas operativos modernos, ejemplos y sus principales funcionalidades

**Escritorio y portátiles (Windows, MacOS, Linux)**
- Monousuario, múltiples aplicaciones.
- Al inicio con poco aislamiento, luego mejoraron seguridad y confiabilidad.
- Objetivos: **interactividad, compatibilidad con muchas apps, aislamiento de fallos y protección contra virus**.

**Smartphones (iOS, Android, etc.)**
- Un usuario, muchas aplicaciones.
- Objetivos: **rapidez de respuesta, variedad de apps, eficiencia energética (batería) y privacidad de datos**.

 **Servidores (ej. web, e-commerce, email)**
- Generalmente un servicio por máquina.
- Objetivos: **alto throughput, mínima latencia, resistencia a ataques y fiabilidad 24/7**.

 **Máquinas Virtuales (VMware, Xen, Virtual PC)**
- Permiten correr varios SO en un mismo hardware.
- Objetivos: **eficiencia, bajo overhead, aislamiento de servicios y flexibilidad en configuración**.

**Sistemas Embebidos (autos, electrodomésticos, dispositivos médicos)**
- SO específico para la tarea.
- Objetivos: **fiabilidad, seguridad, control en tiempo real** (los errores pueden ser críticos).

**Clusters de Servidores (Google, Amazon, etc.)**
- Conjuntos distribuidos de máquinas en centros de datos.
- Objetivos: **tolerancia a fallos, escalabilidad, rapidez, compartición de recursos entre múltiples apps y sitios web**.

### Futuro de los sistemas operativos

Los sistemas operativos han mejorado mucho en **seguridad y resistencia a ataques**, pero aún falta para poder confiar plenamente en ellos en infraestructuras críticas (red eléctrica, hospitales, automóviles). El desafío es garantizar **seguridad, fiabilidad y control preciso**.

Las tendencias de hardware y sociedad marcan hacia dónde deben evolucionar los SO:

 **Centros de datos a gran escala**
- Coordinar cientos de miles o millones de computadoras para servicios globales.

 **Sistemas multinúcleo masivos**
- Los chips con cientos o miles de procesadores exigirán nuevos modelos de paralelismo.

 **Computación portátil ubicua**
- Smartphones, tablets y dispositivos futuros responderán a **voz, gestos e incluso señales cerebrales**, sin depender del teclado/pantalla tradicionales.

**Sistemas heterogéneos**
- Desde supercomputadoras hasta electrodomésticos y sensores (IoT), cada dispositivo será programable y necesitará algún tipo de SO.

 **Almacenamiento a gran escala**
- Se deberá gestionar y preservar cantidades inmensas de datos, accesibles incluso décadas después.



