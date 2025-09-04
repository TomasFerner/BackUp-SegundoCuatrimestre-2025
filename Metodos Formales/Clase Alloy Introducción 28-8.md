## Que es Alloy?

Es un lenguaje formal de modelado, tiene sintaxis y semántica formal definida. las especificaciones se escriben en modo texto (existen representaciones visuals similares a los diagramas de clase UML o los diagramas entidad relación)

Cuenta con una herramienta de verificación llamada **Alloy analyzer**, este analizador puede utilizarse para analizar de manera automática propiedades sobre modelos Alloy

### Para que fue creado

- **Liviano** ya que es pequeño y fácil de utilizar, capaz de expresar propiedades comunes de manera natural
- **Preciso** porque cuenta con una semántica matemática simple y uniforme
- **Tratable** porque el análisis semántico susceptible a ser eficiente y completamente automatizado (considerando limitaciones de alcance)

### Objetivo

La especificación formal de modelos de datos orientados a objetos
Puede utilizarse para modelado de datos en general:
	- Cualquier dominio de individuos y relaciones entre ellos
Resulta util para especificar clases, asociaciones entre ellas y restricciones sobre asociaciones


Para analizar las especificaciones Alloy
- Utiliza verificación limitada:
	Limita el numero de objetos de cada clase a un numero fijo
	Realiza el chequeo para la cantidad de objetos establecida
- Utiliza SAT-solver para responder consultas de verificación
	Convierte las consultas en formulas de lógica booleana e invoca al SAT-solver para responderlas

## Semántica

La herramienta requiere de un lenguaje: 
- para escribir el modelo y 
- para expresar las propiedades

Si se parte de una diagrama de clase: 
• Cada clase corresponde a un conjunto de objetos (átomos) 
• Cada objeto es una entidad abstracta, atómica e inmodificable 
• El estado del modelo está determinado por: 
	Las relaciones entre átomos 
	La pertenencia de los átomos a conjuntos 
	El cambio los átomos y relaciones con el tiempo

### Alloy: Átomos y Relaciones

En Alloy todo se construye a partir de **átomos y relaciones**
• El átomo es la entidad primitiva. Es una entidad:
	 Abstracta y Atómica: no puede dividirse en partes más pequeñas 
	 Inmodificable: sus propiedades no cambian con el tiempo 
	 Interpretable: no tiene propiedades propias 
• Una relación es una estructura que relaciona átomos.
	Define un conjunto de tuplas 
	Cada tupla es una secuencia de átomos

## Ejemplo

![[../Atachments/Pasted image 20250828142715.png]]

• Tamaño de una relación: el número de tuplas en la relación (equivalente a la cardinalidad de conjuntos, #)
• Aridad de una relación: el número de átomos en cada tupla de la relación 

 **Biblioteca** = { (B0) } es una relación de aridad 1 (unaria) y tamaño 1 
 colección = { (B0,L0,A0), (B0,L1,A1) } es una relación de aridad 3 (ternaria) y tamaño 2

![[../Atachments/Pasted image 20250828143608.png]]

![[../Atachments/Pasted image 20250828143725.png]]
## Especificaciones

- **Signaturas** ( signatures )
	Describen las entidades con las que se quiere razonar 
	Definen conjuntos fijos
- **Campos** ( fields )
	Definen relaciones entre signaturas. 
	Es la única manera de incorporar relaciones en Alloy
- **Hechos** ( facts ) 
- **Aserciones** ( assertions ) 
-  **Comandos y alcances** ( commands – scope ) 
-  **Predicados y funciones** ( predicates – functions )
- **Restricciones o constraints simples** (multiplicidad sobre signaturas y/o relaciones)
### Signaturas
Una signatura define un conjunto de átomos (que representa un conjunto base) 
La declaración **sig A { }** define un conjunto de nombre A.

• Un conjunto puede introducirse como una extensión de otro, de la siguiente manera: 
**sig A1 extends A { }**

De esta manera el conjunto A1 es un subconjunto de A, aunque con ciertas restricciones

Las signaturas declaradas de manera independiente son **top-level signatures**

==IMPORTANTE==:
• Las signaturas top-level son disjuntas
• Las diferentes extensiones de una signatura son disjuntas 

Es posible definir signaturas abstractas abstract sig A {} 
Las signaturas **abstractas** no poseen elementos propios, ajenos a las signaturas que las extienden, a menos que no tengan signaturas que las extiendan

Es posible definir signaturas relacionadas por el concepto de subconjunto sig B1 in B {}
### Campos o fields

Las relaciones son declaradas como **campos o fields** de signaturas

Escribir **sig A { f: e}**

introduce al modelo una relación f cuyo dominio es o está incluido en A y cuyo rango está dado por la expresión e

Ejemplo: sig A { f1 : A } **f1 es un subconjunto de A x A**
### Multiplicidades

El uso de la multiplicidad permite definir restricciones en cuanto al tamaño de los conjuntos (signaturas o relaciones).
Se escribe una keyword antes de la signatura, para restringir la cantidad de átomos que define esa signatura

**m sig A {}**

También pueden establecerse restricciones sobre los campos (fields)

**sig A { f: m e} 
sig A { f: e1 m -> n e}**

Hay cuatro keywords de multiplicidad en Alloy: 
1. **set** : cualquier número 
2. **lone** : cero o uno 
3. **some**: uno o más 
4. **one** : exactamente uno
#### Multiplicidades en relaciones binarias

Cada átomo s de S, es mapeado por f a lo sumo a un valor en T **sig S { f: lone T}**

La relación f define una función. La función es parcial

Cada átomo s de S, es mapeado por f a exactamente un valor en T **sig S { f: one T}**

La relación f define una función. En este caso es una función total

#### Multiplicidades en relaciones ternarias

Para cada átomo s de S, el campo f satisface: para cada átomo t de T, f mapea t a exactamente un átomo de U **sig S { f: T -> one U}**

Para cada átomo s de S, el campo f satisface: para cada átomo u de U, a lo sumo un átomo de T es mapeado a u por f **sig S { f: T lone -> U}**

Muchas estructuras relacionales pueden construirse utilizando multiplicidad. 
Por ejemplo:
	sig S { f: some T} (relación total) 
	sig S { f: set T} (relación parcial) 
	sig S { f: T set -> set U} 
	sig S { f: T one -> U}
### Hechos

Son restricciones adicionales sobre signaturas y campos

El analizador de Alloy busca instancias del modelo que satisfagan, también, las restricciones definidas como hechos 

Ejemplo: “Los novelistas y poetas no escriben libros en común”

![[../Atachments/Pasted image 20250828150351.png]]

### Aserciones

Suele ocurrir que el usuario cree que el modelo cumple ciertas restricciones que no son expresadas de manera directa. 

Las aserciones expresan estas restricciones adicionales que el analizador chequea si se verifican 

Si la aserción no se verifica entonces el analizador produce una instancia **contraejemplo** (que ilustra por qué la propiedad falla) 

Si la propiedad expresada como aserción falla, puede ser exprese algo que debiera ser un invariante o bien es necesario refinar la especificación o aserción.

Las aserciones se chequean a través del comando check (el cual debe cubrir el alcance para todas las signaturas )

Ejemplo: Sea A una aserción

![[../Atachments/Pasted image 20250828151017.png]]
### Restricciones

Analizamos que escribir en Alloy, pero no la sintaxis y semántica del lenguaje. 

Con los elementos que contamos hasta ahora no podemos definir restricciones tales como:
- determinar si una relación es simétrica 
- asegurar condiciones con respecto a la naturaleza de la relación.

Para poder comenzar a definir restricciones más interesantes, se agregan tres constantes (que definen tres conjuntos predefinidos): 
• **none** : conjunto vacío 
• **univ** : conjunto universal (formado por todos los átomos de una instancia del modelo) 
• **iden** : conjunto identidad (relación de todos los átomos consigo mismos para una dada instancia del modelo)

### Cuantificadores

![[../Atachments/Pasted image 20250828153255.png]]

### Operadores para conjuntos

![[../Atachments/Pasted image 20250828153350.png]]

Ejemplo: Todos los autores periodistas del libro identificado como book 
{ let book = one Libro { 
	book.escritoPor & Periodista }
}

### Operadores relacionales

![[../Atachments/Pasted image 20250828153449.png]]

### Operadores lógicos

![[../Atachments/Pasted image 20250828160907.png]]

### Producto

p -> q 
• p y q son relaciones 
• p -> q es una nueva relación, esta relación está formada por las tuplas que se forman concatenando cada elemento de p con cada elemento de q

Ejemplo: 
Biblioteca = { (B0)} 
Libro = { (L0), (L1)} 
Autor = { (A0), (A1) } 

Libro -> Autor = { (L0,A0), (L0,A1), (L1,A0), (L1,A1) } Biblioteca -> Libro -> Autor 
= { (B0,L0,A0), (B0,L0,A1), (B0,L1,A0), (B0,L1,A1) }

### Traspuesta

• ~ p • Construye la imagen espejada a la definida por la relación p, es decir contiene tuplas con los átomos invertidos. 
Ejemplo: 
	ejemplo = { (a0,a1,a2,a3), (b0,b1,b2,b3) } 
	~ejemplo = { (a3,a2,a1,a0), (b3,b2,b1,b0) }

### Join: p.q

Sea p una relación de aridad m y q una relación de aridad n, el join es una relación de aridad m+n-2, tal que las tuplas que contiene surgen de combinar los primeros m-1 elementos de cada tupla de p y los últimos n-1 elementos de cada tupla de q, siempre y cuando el join entre las tuplas exista.

El join no está definido en caso que ambas relaciones sean de aridad uno

Ejemplo:
{ (a,b) } . { (a,c) } = { }
 { (a,b) } . { (b,c) } = { (a,c) }
{ (x,b), (y,b), (z,a), (z,c) } . { (b,d), (c,e) } = { (x,d), (y,d), (z,e) }

### Box Join

p|q|  (| son realmente corchetes)
• Semánticamente es idéntico al join anterior, pero toma los argumentos en orden diferente p | q | =  q . p

Ejemplo: 
let mateo = one Autor { // los libros que el autor identificado 
mateo|escritoPor| } // como mateo escribió 
let mateo = one Autor { escritoPor.mateo }//Alternativa equivalente

### Clausura Transitiva

^ r intuitivamente es la aplicación recursiva del operador join entre la relación y sí misma (hasta que no se agreguen tuplas) ^ r = r + r.r + r.r.r + …

![[../Atachments/Pasted image 20250828154249.png]]

### Clausura Reflexivo-Transitiva

![[../Atachments/Pasted image 20250828160121.png]]

Intuitivamente es la clausura transitiva más el conjunto identidad
![[../Atachments/Pasted image 20250828160140.png]]

![[../Atachments/Pasted image 20250828160150.png]]

### Restricciones de Dominio y Rango

Estos operadores se utilizan para filtrar relaciones a un dominio o rango dados 

Si s es un conjunto y r una relación entonces 
	s <: r contiene las tuplas de r que **comienzan** con elementos que están en el conjunto s
	r :> s contiene las tuplas de r que **terminan** con elementos que están en el conjunto s

### Override

**p ++ q**

p y q son dos relaciones de aridad dos o más • El resultado es similar a la unión de p y q, a excepción de que las tuplas de q pueden reemplazar a las tuplas de p. Cada tupla en p que hace match con una tupla de q (comienza con el mismo elemento) es descartada p
**++ q = p – (domain(q) <: p) + q**

Ejemplo: viejaDireccion = { (N0,DO), (N1,D1), (N1,D2) } 
nuevaDireccion = { (N1,D4), (N3,D3) }

**viejaDireccion + nuevaDireccion** = {(N0,DO), (N1,D1), (N1,D2), (N1,D4), (N3,D3) }
**viejaDireccion ++ nuevaDireccion** = { (N0,D0), (N1,D4), (N3,D3) }

### Predicados - Funciones

Pueden utilizarse como “macros” 
- Pueden nombrarse y utilizarse en diferentes contextos (hechos, aserciones, condiciones del comando run) 
- Pueden ser parametrizadas 
- Se utilizan para factorizar comportamiento común 
Predicados 
	Capturan restricciones que el diseñador no desea guardar como hechos 
	Restricciones que se reúsan en varios contextos
Funciones 
	Expresiones que se reúsan en diferentes contextos

### Funciones

Es una expresión nombrada, con cero o más argumentos y provee un resultado

Ejemplo: 
“Los libros que escribió un autor” 
fun escribio |a: Autor|: set Libro { 
	{l: Libro | l in escritoPor.a } }

### Predicados

Es una restricción nombrada, con cero o más argumentos Los predicados no se incluyen en el análisis a menos que sean referenciados en los esquemas que se analizan (run, aserción, hecho) 

Ejemplo: 
“¿Es autor de un libro?” 
pred esAutorDe |a: Autor, l:Libro| { a in l.escritoPor }
## Buscando instancias del modelo

El comando **run** se utiliza para indicarle al analizador de Alloy, que genere una instancia del modelo 

El comando puede incluir condiciones: 
- se lo puede guiar para elegir instancias con ciertas características (por ejemplo forzar a que ciertos conjuntos y relaciones sean no vacíos)
- las condiciones que se agregan al comando no son parte de la especificación “real”.

El algoritmo que implementa el analizador prefiere instancias pequeñas 
- Suele producir instancias vacías o triviales 
- Igualmente es útil saber que estas instancias satisfacen las restricciones impuestas (ya sea porque se espera que así sea o no) 

Es usual que las instancias mostradas no muestren todos los comportamientos interesantes que son posibles
## Debilidades de los modelos construidos

El modelo es **irrestringido – sin restricciones** 
Hay conocimiento de nuestro dominio que no es considerado. 
Es posible agregar **restricciones o constraints** para enriquecer el modelo 

En las primeras etapas del proceso de desarrollo es común contar con modelos sin restricciones. 
Alloy provee un feedback rápido sobre las debilidades del modelo Se puede ir agregando restricciones hasta que estemos satisfechos con él.

