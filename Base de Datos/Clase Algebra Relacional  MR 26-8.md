Conceptos MER y MR: [[Clase Continuación Introducción 22-8]]

## Algebra Relacional

El álgebra relacional (AR) está definido en base a un grupo de operadores que permiten describir paso a paso cómo resolver una consulta «operando» sobre las relaciones existentes en una base de datos. 

Los operadores «exigen» como parámetro de entrada una o más relaciones y dan como respuesta una relación 

Operadores básicos del AR: 
→ Sobre conjuntos de tuplas: Unión, Diferencia, Producto Cartesiano 
→ Específicos para bases de datos relacionales: Selección, Proyección, Join.

### Convención de notación

![[../Atachments/Pasted image 20250826160343.png]]

El algebra relacional es un lenguaje para operar sobre relaciones del modelo relacional. Está dentro de los lenguajes puros orientado a procedimientos.

![[../Atachments/Pasted image 20250826160510.png]]

### El operador de Selección 

El operador **selección** aplicado sobre una relación r, genera una **relación resultado**. El resultado contiene el **subconjunto de tuplas de r que satisfacen una condición de seleccion**.

El operador selección funciona como un «filtro» que recupera las filas de la relación r que satisfacen la condición de filtro. 

El resultado de Sigma p (r) es una nueva relación con el mismo esquema de r y como instancia, las tuplas de r que satisfacen con la condición de filtro.

Se define como:

![[../Atachments/Pasted image 20250826160635.png]]

![[../Atachments/Pasted image 20250826160646.png]]

p es una fórmula del cálculo proposicional, consiste de términos conectados por : (and),(or),(not)
cada término es de la forma:
	**'atributo' op 'atributo' o 'constante'**

Siendo operando op:
 ![[../Atachments/Pasted image 20250826161002.png]]

Ejemplo Operador de selección

![[../Atachments/Pasted image 20250826161204.png]]


Ejemplo 2 Operador de Selección

![[../Atachments/Pasted image 20250826161247.png]]

#### Selección en SQL 

![[../Atachments/Pasted image 20250826162229.png]]

SELECT * 
	FROM vuelos 
	WHERE desde= “JFK” AND hacia=“Boston”;

### Operador de Proyección 

Sea r, r(R); y sea X un subconjunto de atributos de R, X contenido en R. Se define como «proyección de los atributos X de r»

![[../Atachments/Pasted image 20250826161752.png]]

![[../Atachments/Pasted image 20250826161815.png]]

Donde X = (A1 , A2 … Ak ) son nombres de atributos

El operador **proyección** aplicado sobre una relación r, genera una relación resultado que tiene un subconjunto de atributos o columnas de r. 
- La relación resultante tiene k columnas. 
- Bajo la teoría de conjuntos, una relación no posee tuplas o filas repetidas, en PI X (r) se eliminan de r las tuplas (filas) repetidas.

Ejemplo operador de proyección

![[../Atachments/Pasted image 20250826162019.png]]

#### Proyección en SQL

![[../Atachments/Pasted image 20250826162153.png]]

SELECT nro-vuelo, salida, llegada 
	FROM vuelos;


### Proyección + Selección

Dar el número de identificación de los caballos que ganaron alguna carrera

![[../Atachments/Pasted image 20250826162511.png]]

### Operador Unión

El operador unión participan dos relaciones r y s se define como:

![[../Atachments/Pasted image 20250826162551.png]]

Pare que la operación r union s sea válida debe cumplirse:
1. r, s deben tener la misma aridad (el mismo número de atributos). 
2. Los dominios de los atributos de r y s deben ser compatibles.
De acuerdo con la teoría de conjuntos, en la unión de relaciones se eliminan tuplas repetidas

Ejemplo Union

![[../Atachments/Pasted image 20250826162730.png]]

#### Union en SQL

SELECT dapellido, dnombres 
	FROM dueño 
	UNION (SELECT japellido, jnombres FROM jinete);