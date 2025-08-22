[[Lectura Opcional The worlds of database systems]]
## ¿Cómo está organizada la materia? 

1.Diseño del Modelo de Datos 
	- Diseño conceptual del modelo de datos de un problema: Modelo Entidad Relación. 
	- Modelos de datos lógico: el Modelo Relacional. Fundamentos teóricos. 
	- Modelos físicos para almacenar datos persistentes. 

2.El software de Gestión de Bases de Datos (SMBD) 
	- SMBD centralizado y distribuido 
	- Componente de Transacciones 
	- Componte de recuperación de datos 
	- Transacciones Distribuidas 

3.Conceptos distinguidos por materia

## Definición de Conceptos

Una **DB (data base)** es una colección organizada de elementos de datos interrelacionados de un negocio, estos datos tienen diferente tamaño y pueden ser compartidos por diferentes usuarios, se busca modelar datos persistentes, representan a una parte de un dominio o universo

La base de datos puede ser **centralizada** en una computadora o **distribuidas** en varias computadoras

Los datos son interrelacionados ya que tienen relaciones entre si

Estas BD usan un software llamado **Sistema de manejo o gestion de bases de datos (DBMS/Motor de base de datos)**, es una colección interrelacionada de programas preparados para administrar datos, son responsables del almacenamiento eficiente y de la recuperación de elementos de una BD

Para hacer la administración de los datos mas convenientes, generalmente se encapsula a las bases de datos dentro de la DBMS

![[Pasted image 20250819150814.png]]

### Problemas
**Redundancia e inconsistencia de datos:** Aplicaciones desarrolladas en diversos lenguajes «almacenan» datos en archivos con diferentes estructuras. Se repiten datos: aumenta el costo en espacio y las posibilidades de inconsistencia. 

**Dificultad para acceder a los datos:** Un requerimiento de acceso a los datos no considerado requiere del desarrollo de un nuevo programa. Ejemplo: un nuevo listado. La información está distribuida en varios «archivos».

**Problemas de integridad:** La confiabilidad de las datos depende de que se satisfagan algunas restricciones de consistencias. Ejemplo: no deben existir dos personas con el mismo número de CUIL.

**Aislamiento de datos:** Datos distribuidos en varios archivos, con formatos diferentes oscurece los programas de aplicación. 

**Problemas de Atomicidad:** Los sistemas están sujetos a fallos. En ciertas operaciones es crucial que si se produce un fallo, los datos vuelvan al estado inmediatamente anterior al fallo. 
Ejemplo: un fallo en la mitad de una transferencia.

**Anomalías de acceso concurrente:** Cuando se permite que múltiples usuarios accedan y actualicen el contenido de la base de datos en forma simultánea, las interacciones por actualizaciones concurrentes pueden resultar en datos inconsistentes. 

**Seguridad:** No todos los usuarios deben tener acceso a todos los datos. Ejemplo: permisos de acceso diferentes de los EMPLEADOS y el SUPERVISOR.

## Servicios del Sistema de Gestión de Bases de Datos (DBMS):

1. Contar con al menos un **modelo de datos**. 
2. Disponibilidad de **Lenguajes de alto nivel** para administrar y manipular la base de datos 
	- Lenguaje de Manipulación de Datos (LMD/DML). 
	- Lenguaje de Definición de Datos (LDD/DDL). 
3. **Acceso eficiente** al consultar y recuperar los datos almacenados. 
4. Contar con **manejo de transacciones** (commit y rollback). 
	- Mantener **integridad y consistencia** de datos. 
	- Provea **control de concurrencia** y capacidades para **compartir datos.** 
	- Permita **recuperaciones de fallos.** 
5. Brindar facilidades de **seguridad** y facilidades en la **administración de datos**

### Modelo de datos

Un modelo de datos  brinda una colección de herramientas para: 
	→ Describir los datos. 
	→ Describir relaciones entre los datos. 
	→ Describir la semántica de los datos. 
	→ Describir restricciones de integridad.

Existen distintos tipos de modelos de datos 
	→ Modelos conceptuales basados en objetos. 
	→ Modelos lógicos basados en registros. 
	→ Modelo Físicos
### SMDB: Visión de los datos 
Uno de los propósitos del SMBD es ofrecer a sus usuarios una **visión abstracta de los datos** 
Los DBMS definen tres niveles de abstracción para los datos:
1. **Nivel Físico o interno**, suele depender de la máquina 
2. **Nivel Lógico o conceptual**. De desarrollo y basado en el modelo de datos. 
3. **Nivel de Vista** como se ven los datos «afuera»
### Nivel de abstracción de datos

![[Pasted image 20250819153612.png]]

**Nivel Físico** 
	• Es el nivel de menor abstracción.
	• Define cómo los datos son efectivamente almacenados.

**Nivel Lógico** 
	• Abstracción media 
	• Describe cómo se distribuyen y cómo se relacionan en término de un conjunto reducido de estructuras simples.
	• Oculta la representación física de los datos.

**Nivel Conceptual y de Vista** 
	● Más abstracto. 
	● Describe “partes” de la base de datos. 
	● Un sistema puede proveer varias vistas de la misma base de datos

### Instancia y Esquema

El contenido de la base de datos es dinámico, i.e., cambia constantemente en la medida que se agrega, borra o modifica información. Sin embargo, la estructura que contiene los datos es estable. Así, se distingue:
-  **Esquema de bd**: el diseño de la base de datos. Los esquemas raramente se modificacion
	Ejemplo: el esquema de libros incluye los atributos ISBN, título, autores, área de aplicación. 	
- **Instancia de bd**: los datos almacenados en un instante particular. 
	Ejemplo: la instancia que tiene datos de los libros de la biblioteca del DCIC.

## Modelados
### Modelo Entidad/Relación (MER) 

**Modelo Entidad-Relación (Nivel Conceptual – Basado en Objetos)** 
Se basa en una percepción del mundo real que consiste de una colección de objetos básicos llamados entidades y las relaciones entre dichas entidades. 
Cada entidad tiene asociado atributos que la describe. 

Ejemplo: 
- La entidad materia tiene los atributos código, nombre, carga horaria que la describen. 
- Una entidad materia se relaciona con una o más entidades docente por la relación dicta

 **Diagrama Entidad-Relación (DER)**
La expresión gráfica del Modelo Entidad Relación se denomina diagrama entidad-relación. El Diagrama Entidad-Relación (DER) se compone de: 
→ Rectángulos: representando conjuntos de entidades. 
→ Elipses: representando atributos. 
→ Rombos: representando relaciones entre conjuntos de entidades. 
→ Líneas: vinculando conjuntos de entidades entre sí o conjuntos de entidades con relaciones.

![[Pasted image 20250819154433.png]]

### Modelo Orientado a Objetos (OO)

**Modelo Orientado a Objetos (Nivel Conceptual – Basado en Objetos)**
Se basa en una colección de objetos y su asociaciones.
Sobre objetos:
→ Tiene valores almacenados dentro de sus variables de instancia.
→ Responde a código (denominados métodos) que operan sobre el objeto.
→ Los objetos con estructura similar y los mismos métodos se agrupan en clases.
→ Los objetos acceden a datos de otros objetos mediante el envío de mensajes.

### Modelo Relacional

**Modelo Relacional (nivel lógico basado en registro):**
→ La BD se estructura en registros de formato fijo. 
→ Cada registro tiene un número fijo de atributos o campos de longitud fija. 
→ Considera la BD como una colección de tablas para representar datos y relaciones. 
→ Cada tabla está formada por columnas distinguidas por su nombre. 
→ Es un modelo orientado a registro. 
→ Es el modelo de datos más usado a nivel comercial.

![[Pasted image 20250819155000.png]]

### Modelo Semiestructurado

**Modelos de Datos Semi-Estructurados**
● Permite especificar datos donde ítems individuales del mismo tipo que difieren en sus atributos. ● Los datos semiestructurados se definen usando alguna variante de XML (Extensible Markup Languaje). 
● Las capacidades para especificar tags y crear estructuras anidadas hace posible manejar también datos. 
● Existe una variedad de herramientas disponibles para chequear, mostrar y consultar datos XML.

##  Lenguajes de Bases de Datos 

Los SMBD proveen dos tipos de lenguajes: 
-  **Lenguaje de Definición de Datos (LDD/DDL):**
	lenguaje que permite especificar mediante un conjunto de sentencias el esquema de una base de datos. 
- **Lenguaje de Manipulación de Datos (LMD/DML):**
	es el lenguaje que nos permite modificar y consultar la información almacenada en una base de datos, ie. manipular instancias.
### Lenguaje de Definición de Datos

Cuenta con sentencias que permiten realizar acciones como: 
- **Recuperar** información almacenada en la BD. 
- **Agregar** nueva información a la BD. 
- **Borrar** información de la BD. 
- **Modificar** información de la BD. 

Los lenguajes pueden ser: 
● Procedimentales/Operacionales: especifican qué datos se necesitan y cómo obtenerlos. 
● Declarativos/No Procedimentales: especifican qué datos se necesitan sin especificar como obtenerlos.

## Manejo de Transacciones

Una **transacción** es una colección de operaciones que realizan una única función lógica en una aplicación de base de datos.

Entre los servicios que ofrece el DBMS está la capacidad de manejar **transacciones.**
Ejemplo: 
	Sea la transacción que transfiere $50 pesos desde una cuenta A a una cuenta B. 
	1. Esto es, debitar $ 50 de A. 
	2. Acreditar $ 50 en B. La transferencia debe ser una única operación lógica->una transacción

- Asegurar **consistencia** en la base de datos es responsabilidad del programador.
- Asegurar las propiedades **atomicidad y durabilidad** es responsabilidad del SMBD, particularmente del componente Gestor de Transacciones.
- Si **varias transacciones actualizan en forma concurrente** la base de datos, la consistencia no puede dejar de ser preservada. Es responsabilidad del **Gestor de Control de Concurrencia** controlar la interacción de las transacciones concurrentes con el fin de preservar consistencia en la base de datos.

### Ejemplo transferencia

- La transacción T debe realizarse de manera completa: ejecutarse con éxito el débito en A y el crédito en B. El requerimiento «todo-o-nada» → **atomicidad.** 
- Una vez que se ejecutó con éxito la transacción T, se debe preservar la consistencia de la BD, esto es, la suma de A+B debe ser igual a la anterior → **consistencia.** 
- Después de la ejecución exitosa de T, los nuevos valores de las cuentas A y B deben persistir, a pesar de la posibilidad de fallas en el sistema → **durabilidad.** 
- Cada transacción es una unidad de atomicidad y consistencia que no debe violar las restricciones de la base de datos, aún si otras transacciones se están ejecutando sobre los mismos datos → **aislamiento.**
## Arquitectura del SMBD y Usuarios de una BD

Para proveer sus servicios un SMBD cuenta con componentes organizados según su responsabilidad: 
	- Procesamientos de consultas 
	- Administradores de almacenamiento.

La arquitectura de DBMS está fuertemente influenciada por la arquitectura física del HW donde este corriendo: centralizado, cliente-servidor, arquitecturas paralelas, o distribuidas.

A nivel de aplicaciones, generalmente las aplicaciones se conectan el SMBD a través de la red, diferenciándose la máquina cliente-maquina servidor.

![[Pasted image 20250819161408.png]]

### Usuarios de la BD

Un sistema de base de datos provee un entorno para obtener o almacenar información en la BD. Existen distintos tipos de **usuarios**: 
- **Administrador de bases de datos.**
- **Programadores** de Aplicación: desarrolladores. 
- **Usuarios Sofisticados**: interactúan con la base de datos usando lenguajes de consulta. 
- **Usuarios Ingenuos**: quienes interactúan usando programas de aplicación permanentes.
### Administrador de una Base de Datos

El administrador de base de datos (ABD/DBA) es la persona que cumple el rol de responsable de configurar y administrar el SMBD. Sus principales funciones son: 
- Definir esquemas. 
- Definir estructuras de almacenamiento y métodos de acceso. 
- Modificar esquemas y organización física. 
- Conceder autorización para el acceso de los datos. 
- Especificar restricciones de integridad. 
- Asegurar la performance del sistema.

## Modelo Entidad-Relacion en profundidad

==El modelo de datos debería ser “general” y “completo”, idealmente no se tendría que modificar con frecuencia.==

Modelo Entidad Relación (MER) es un modelo que se utiliza para alcanzar el diseño conceptual de un negocio o empresa. Se basa en la percepción del mundo real como la colección de: 
	• Objetos básicos llamados **entidades**. 
	• Y **relaciones** entre las entidades.

### Entidad
Es un objeto, concreto o abstracto, que existe y se distingue de otros objetos. 
Ejemplos: el cliente Andrés Mora, número de CUIL 20-30284671-4 es una entidad que identifica únicamente a un cliente. 

### Conjunto entidad
Es un «conjunto» o agrupación de entidades de un mismo tipo y que comparten propiedades o atributos. 
Ejemplos: el conjunto de todas las personas que tienen cuenta en un banco define al Conjunto Entidad CLIENTES.

**Propiedad**: Dos conjuntos entidad no necesariamente tienen que ser disjuntos.
Ejemplos: conjunto entidad DOCENTES y conjunto entidad ALUMNOS de la UNS, un ayudante alumno es miembro de ambos conjuntos

![[Pasted image 20250819163416.png]]

La relación entre la entidad débil y su entidad fuerte es de identidad, esto es, es siempre de m:1. 
Discriminador: es el atributo/s de la entidad débil que la distingue como entidad subordinada. Ejemplo: 
	• Nro_ejemplar es el discriminador de EJEMPLARES 
	• Nro_Cuota es el discriminador de CUOTAS. 
La llave primaria para un conjunto de entidades débil A subordinado al conjunto de entidades fuertes B: Llave primaria(B) **UNION** Discriminador(A)
### Conjunto Entidad Fuerte

Un conjunto entidad es **fuerte** si contiene uno o más atributos que lo distinguen, esto es, tiene atributos que operen como llave primaria.
Ejemplo: 
	• Sea el conjunto entidad LIBROS, el atributo ISBN identifica a un “único” Libro
Conjunto de Entidades Fuerte -> Dominante 
Conjunto de Entidades Débil -> Subordinada
### Conjunto Entidad Débil

Se dice que un conjunto entidad es **débil** si entre sus atributos NO cuenta atributos suficientes para definir la llave primaria.
Ejemplos: 
	• El conjunto entidad Ejemplares de Libros:
		**Ejemplares**(Nro-Ejemplar, Fecha-Adquisición y Precio-Compra)
### Atributos
Cada entidad está representada por un conjunto de atributos. 
• Para cada atributo se define el **conjunto de valores permitidos:** el dominio del atributo. 
• Formalmente, cada atributo es una función que asigna a entidad.atributo un valor de dominio. (Persona.nombre → «José», Persona.apellido → «Salinas»)

Entre los atributos que describen a las entidades se distingue el/los atributo/s que cumplen el rol de identificador o llave o clave 
Se denomina así al/los atributos que **identifican unívocamente a una entidad** del conjunto entidad.

Ejemplo: Conjunto entidad **TRANSACCION**: 
	**TRANSACCION** (nro-Transaccion, tipo-Transaccion, fecha, monto).

Los atributos pueden ser:
1. **Simples o compuestos:**
		• Simples: no dividen en subpartes. Ejemplo: nro-transacción. 
		• Compuestos: pueden ser divididos en subpartes.
		 Ejemplo: persona-domicilio compuesto por calle, número, piso, departamento 
2. **De valor único o multivalores:**
		• Multivalores: con más de un valor del atributo para la entidad individual. 
		 Ejemplo: nros-Teléfonos. 
3. **Derivados:**
		• Se obtienen a partir de otros atributos o entidades. 
		 Ejemplo: el atributo edad se obtiene del atributo fecha_nacimiento.
### Relación y conjunto relación

**Relación (relationship)**: es la asociación o relación entre dos o más entidades. 
	“Mercedes Vitturini” **dicta** “Elementos de Bases de Datos”.
**Conjunto Relación (relation set)**: es el conjunto de relaciones de un mismo tipo. 
	**Dictan** relaciona una entidad de Docentes con alguna entidad de Materias.

![[../Atachments/Pasted image 20250819164541.png]]

Las relaciones eventualmente pueden tener **atributos** propios
	La relación cursa entre entidades MATERIAS y ALUMNOS podría incluir los atributos año, cuatrimestre y resultado
### Cardinalidad de Relaciones o Multiplicidad
determina el número o cantidad de entidades con las que otra entidad se asocia a través de una relación. 
Para conjuntos relación binarios la cardinalidad puede ser: 
→ Uno a uno (1:1). 
→ Uno a muchos (1:m). 
→ Muchos a uno (m:1). 
→ Muchos a muchos (m:n).

**Grado de un conjunto relación** se define por el **número de entidades** que participan.
• Un conjunto relación que involucra a dos entidades se dice binario.
• Otros grados: ternarios, cuaternarios, … n-arios

Ejemplo: 
	La relación **comisiónDeCursado** entre los conjuntos entidad ALUMNOS, MATERIAS y DOCENTES.
### El Diagrama Entidad Relación

La estructura lógica de una base de datos se puede expresar de forma gráfica en el Diagrama Entidad-Relación (DER). 
Un DER está compuesto de: 
- **Rectángulos**: representan a conjuntos entidad. 
- **Elipses**: representan atributos. Se distinguen 
	• Elipses con borde doble: para atributos multivaluados. 
	• Elipses con borde punteado: para atributos derivados. 
- **Rombos**: representan conjuntos relación entre conjuntos entidad. 
- **Líneas**: vinculan conjuntos entidad y atributos o conjuntos de entidad y conjuntos relación.

![[../Atachments/Pasted image 20250819170543.png]]
![[../Atachments/{533F3F0D-46C1-4F8D-84E4-A010043C4FC5}.png]]
### Llaves

**Superllave**: es uno o más atributos del conjunto entidad que distingue unívocamente a un elemento del conjunto de entidad. 
- Nro-Seguridad-Social es superllave del conjunto de entidades Cliente. 
- Nro-Seguridad-Social y Nombre-Cliente es superllave del conjunto de entidades Cliente. 

**Llave Candidata**: es una superllave que no contiene un subconjunto propio que sea superllave. Es decir, es una superllave minima. 

**Llave Primaria**: es una llave candidata elegida por el diseñador de la base de datos.
### Atributos De Relación

Sean los conjuntos entidad: 
	Alumno ($nro-Registro$, nombre, domicilio, ciudad) 
	Materia ($id-Materia$, nombre-Materia, carga-Horaria) 

La relación **rinde-examen** asocia a las entidades alumno con las entidades de materia que rinde. • Los atributos **fecha y nota** describen a Rinde, quedando definida como: 
	**rinde-examen** (alumno, materia, Fecha, Nota)

### Relaciones ternarias

![[../Atachments/Pasted image 20250822161829.png]]

En el ejemplo 
	- Dados una entidad **empleado** y una **sucursal**, el **empleado** trabaja en un único **area** en dicha **sucursal** . 
	- Dados un **empleado** y un **area** , el **empleado** trabaja en “muchas” **sucursales** en el mismo **area** . 
	- Dados una **sucursal y una **area** , en la **sucursal** “muchos” **empleados** trabajan en dicha **area**.

## Diagrama Entidad Relación Extendido (Conceptos avanzados)

### Especialización

concepto que define a un conjunto entidad que puede contener subconjuntos propios de entidades diferentes entre si (diseño top-down), es el proceso de indicar subgrupos en un conjunto de entidades.

### Generalización

concepto que determina que a partir de distintos subgrupos de conjunto entidad, puede obtenerse un super conjunto entidad más general (diseño bottom-up), es el proceso de crear un (super)conjunto de entidades a partir de conjuntos de entidades particulares

**Ambas se representan con la relación distinguida “IS-A” o ES-UN”.**

![[../Atachments/Pasted image 20250822163200.png]]

### Restricciones de Diseño para ES-UN

**Restricciones de completitud**: especifican si una entidad en un conjunto de entidades de nivel más alto debe pertenecer al menos a un conjunto de entidades de nivel más bajo, la restricción puede ser Total o Parcial 
	• Para el ejemplo de cuentas, una cuenta es de ahorro o cheque **(total)**

**Restricciones de pertenencia**: Sobre los conjuntos entidad de nivel inferior (especialización):
• **Disjuntos**: cada entidad pertenece, a lo sumo, a un conjunto de entidades de nivel inferior. 
• **Solapados**: la misma entidad puede pertenecer a más de un conjunto de entidades de nivel inferior. 
	Ejemplo: una cuenta puede ser de ahorros o de cheques, pero no ambos (disjunto).

### Agregación

Una limitación del modelo entidad relación original es que no es posible expresar relaciones con relaciones.

Es la abstracción por la cual una relación junto con las entidades que vincula, se trata como si fuera un nuevo **conjunto entidad**.

El nuevo conjunto entidad que resulta de la agregación se considera como cualquier otro conjunto entidad.

![[../Atachments/Pasted image 20250822163953.png]]

- Se requiere de R1 para definir R2 . 
- Pueden existir elementos de R1 que no estén en la relación R2 pero no a la inversa.

![[../Atachments/Pasted image 20250822164259.png]]

¿Tiene sentido mantener ambas relaciones?

![[../Atachments/Pasted image 20250822164339.png]]

## Guía básica para construir un MER

1. Identificar las **entidades** y definir los **conjuntos de entidades**.
	   Identificar los **atributos que describen las entidades**.
2. Identificar las **relaciones** entre las entidades. 
	   Identificar **atributos asociados con las relaciones** (si existen). 
3. Analizar y definir la **cardinalidad** de las relaciones. 
4. Identificar la oportunidad de **usar los conceptos más avanzados** (entidades débiles, generalización-especialización, agregación).
