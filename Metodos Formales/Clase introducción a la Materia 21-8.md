==version Alloy 5.1 usado en la primera mitad de la materia==

==después del parcial usaremos alloy 6.2==

## Conjuntos y Relaciones

Logica de primer orden es el calculo de predicado

El problema de el calculo de predicados es que en su completitud no es computable 
En la lógica de primer orden las cosas que cuantificamos son átomos, estos mismos no tienen identidad, para el calculo de predicado todos los átomos son iguales

Como en un programa lo primero que queremos saber es con el tipo de datos que estamos trabajando, necesitamos poder escribir estas restricciones de manera lógica

Ejemplo: 
**para todo x tal que edad(x) > 18**
podemos probar que esto se cumple, sin embargo no podemos saber si eso solo se aplica a cosas de un mismo tipo, es decir si solo se aplica al átomo persona

por ende tenemos que lograr incluir cuantificadores para un tipo especifico de átomos, básicamente estamos agregando la funcionalidad de trabajar con tipos (conjuntos y relaciones) 

==Lo que estamos escribiendo es un modelo no un programa, lo que estamos ejecutando es una instancia del modelo que creamos==

Un **conjunto** es una colección de objetos distintos, su idea principal es ordenar elementos o atomos, cada conjunto base se construye a partir de un dominio de objetos(en este contexto los conjuntos son homogéneos)

### Conjunto base
Los **conjuntos base** están formados por valores del mismo dominio

los conjuntos base se pueden definir por **enumeración**(listando elementos) o por **comprension**(dando una propiedad que defina al conjunto), la enumeración solo es viable bajo escenarios que sean finitos y reducidos, por lo generar en alloy usaremos la definición de compresión

### Cardinalidad
La cardinalidad de un conjunto, notado con el símbolo # esta definida como la cantidad de elementos de ese conjunto

en una partición de conjuntos, los mismos son **disjuntos** no comparten elementos en común

==La aridad de un conjunto base es siempre 1==
Ejemplo
	Dominio Básico: residencia
	Particiones: Departamentos, casa, hogar, pieza
todo elemento dentro de la partición esta dentro del dominio básico
### Aridad
La **aridad** de un conjunto es la cardinalidad de cada elemento de un conjunto

### Relaciones
Son la manera de hacer referencias a valores estructurados
	grupo de valores que están relacionados
	conjunto de tuplas
	se definen a partir de **conjuntos base**
Ejemplo
**Conjunto base**: Entero, Natural
Relaciones
	cuadrados: relaciona un numero entero con un natural siendo el natural el cuadrado del numero entero
	cuadrados = {(-1,1),(2,4),(-3,9),(3,9)}
	Dondo el dominio es {-1,2,-3,3} y el rango es {1,4,9}
==Para alloy todo termina siendo una relación==

No se convierten a relación binarias sino a relaciones planas, en una relación binaria el primer valor es el dominio y el segundo es el rango

en matemática todas las relaciones son binarias

==en nuestro contexto el dominio es un conjunto y el rango es un conjunto sin importar al aridad de la relación==

Tanto para **relaciones** como para **conjuntos base**, pueden utilizarse la operación habituales para conjuntos (pueden ser aplicadas solo en relaciones de la misma aridad)
	union +
	intersección &
	diferencia -
### Producto

el producto de 2 relaciones A( de aridad n) y B (de aridad m)es la relación AxB ( de aridad n+m) tal que los primeros n elementos corresponden a una tupla de la relación A y los restantes m elementos a una tupla de la relación B

Ejemplo
A = {a1,a2} B= {b1}
c = AxB = {(a1,b2),(a2,b1)}

D={d1,d2}
e = Dxc = {(d1,a1,b1),(d1,a2,b1),(d2,a1,b1),(d2,a2,b1)}

==básicamente, toda relación es un producto de conjuntos base o un subconjunto de dicho producto==


### Dominio y rango

el **dominio** de una relación es el conjunto de átomos que aparecen como primer elemento en las tuplas q la definen

el **rango** de una relación, es el conjunto de átomos que aparecen como ultimo elemento en las tuplas que la definen

### Estructuras comunes de una relación

- Uno a muchos
- Muchos a uno
- Uno a uno
- Muchos a muchos

### Relaciones funcionales

una función es una relación de aridad n +1 que no puede contener dos tuplas diferentes para los primeros n elementos

==No todas las relaciones son funcionales, algunas de ellas son funcionales==

Una función es **total** si esta definida para todos los valores del dominio
Una función es **parcial** si esta definida para algunos valores del dominio

Es una función inyectiva si define una relación uno a uno
	puede haber relaciones inyectivas que no sean funcionales
Es una función sobreyectiva si cubre todo el rango definido
Es una función biyectiva si resulta ser inyectiva y sobreyectiva

![[../Atachments/Pasted image 20250821160511.png]]


### Composición

La composición permite generar una nueva relación a partir de dos relaciones 
• La relación nueva mapea el dominio de la primer relación al rango de la segunda
• Dada s: A x B y r: B x C entonces s; r: A x C
; es el símbolo de composición
![[../Atachments/Pasted image 20250821160710.png]]

### Clausura

Intuitivamente, la clausura de la una relación, es la composición continua de la misma hasta que no se consigan

• Sea r: S x S

![[../Atachments/Pasted image 20250821160758.png]]

### Traspuesta

Intuitivamente, la relación traspuesta está formada por los pares reversos de los que componen la relación original

• Sea r: S x T

![[../Atachments/Pasted image 20250821160844.png]]

