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

![[../Atachments/Pasted image 20250829161444.png]]

Ejemplo Union

![[../Atachments/Pasted image 20250826162730.png]]

#### Union en SQL

SELECT dapellido, dnombres 
	FROM dueño 
	UNION (SELECT japellido, jnombres FROM jinete);

### Operador Diferencia

El operador diferencia entre dos conjuntos de relaciones r y s se define como:

![[../Atachments/Pasted image 20250829161348.png]]

Para que la diferencia de conjuntos sea posible las relaciones tienen que ser compatibles:
	• r y s deben tener la misma aridad. 
	• Los dominios de los atributos de r y s deben ser compatibles.

• Notación: r – s ó r / s

![[../Atachments/Pasted image 20250829161426.png]]

Ejemplo diferencia:

![[../Atachments/Pasted image 20250829161525.png]]

#### Diferencia en SQL

```
SELECT * 
 FROM dueño 
 MINUS 
 (SELECT jdni, japellido, jnombres FROM jinete);
 ```

### Producto Cartesiano (X)

El producto cartesiano entre dos relaciones r y s se define como:

![[../Atachments/Pasted image 20250829161738.png]]

Cada tupla t de r se combina con cada tupla q de s.

![[../Atachments/Pasted image 20250829161955.png]]

¿Nombre y edad de Caballos salieron segundos?

![[../Atachments/Pasted image 20250829162742.png]]

¿Nombres y apellidos de las personas que son a la vez dueños y jinetes?

![[../Atachments/Pasted image 20250829162825.png]]

Si un atributo A está en r y está en s, en el Producto Cartesiano existe como dos columnas y se distinguen por el «nombre de la relación» : r.A y s.A
#### Producto cartesiano en SQL

SQL hace el producto cartesiano de las relaciones que aparecen listadas después de FROM Las relaciones que se listen después de la palabra reservada FROM deber estar separadas por comas. Detrás de FROM pueden listarse cualquier cantidad de relaciones. 
SQL genera el producto cartesiano de todas ellas.

```
SELECT* 
	FROM vuelos, pasajeros
```

### Operador Renombrar (p)

El operador renombrar permite nombrar resultados de expresiones del álgebra relacional.

Ejemplo: 
• Sea r(A1 ,A2 ,…,An ) una expresión del Algebra Relacional de aridad n

![[../Atachments/Pasted image 20250829162947.png]]

Retorna las tuplas de r bajo el nombre s y sus atributos nombrados como a B1 , B2 , …, Bn .

#### Operador renombrar en SQL

![[../Atachments/Pasted image 20250829163231.png]]

renombra el resultado en dos sentidos
• A la relación caballo como horse 
• Y a sus atributos número, nombre, edad y peso por number, name, age, weight

```
SELECT nroCaballo as number, 
nombre as name, 
edad as age, 
peso as weight 
FROM caballo as horse;
```

### Operador intersección

El operador intersección toma dos relaciones r y s, y define r intersección s como:

![[../Atachments/Pasted image 20250829163742.png]]

Como ocurre con los operadores unión y diferencia, requiere que:
• r, s tengan las misma aridad.
• Los tipos de los atributos de r y s son de tipos compatibles.

Observación: el operador intersección se define a partir de la diferencia:

r intersección s = r – (r – s)

![[../Atachments/Pasted image 20250829163857.png]]

![[../Atachments/Pasted image 20250829164053.png]]

### Operador Join-Natural

Sean r(R) y s(S), el operador "fusión (join) natural de r y s", notado como r join-natural s, contiene el conjunto de tuplas t que tienen como esquema R union S, y tal que

![[../Atachments/Pasted image 20250829164212.png]]

donde R intersección S = {A1 ,A2 ,…,An }.

![[../Atachments/Pasted image 20250829164325.png]]

==Si las relaciones no comparten atributos es equivalente al Producto Cartesiano==

En muchas ocasiones se utiliza simplemente el término join en alusión al join natural.

![[../Atachments/Pasted image 20250829164532.png]]

otro ejemplo:

El nombre de los caballos que corrieron alguna carrera.

![[../Atachments/Pasted image 20250829164726.png]]

### Operador Theta Join

Dadas dos relaciones r y s, el operador theta-Join se define como:

![[../Atachments/Pasted image 20250829165006.png]]

Un operador theta-Join realiza el producto cartesiano de dos relaciones y luego resuelve la selección usando el predicado relacional theta.

El esquema de r ⋈-theta s es R+S (todos los atributos de R y todos los atributos de S) 

Theta-Join permite combinar relaciones con restricciones particulares. 
	theta es un operador relacional: { >, <, , >=,<=, =, =/ }.

Ejemplo:
Recuperar el nombre de los caballos mayores de 8 años que ganaron alguna carrera.

![[../Atachments/Pasted image 20250829165207.png]]

### Operando Outer Join


La operación outer join es una extensión de la operación join para evitar la pérdida de información si no existen tuplas que coincidan en los atributos compartidos. 
1. Calcula el join y luego se agregan las tuplas que no hacen match con las tuplas de la otra relación del join. 
2. Usa valores nulos o indeterminado en los atributos que no se puede determinar el valor.
3. null significa que el valor es desconocido o no existe.

Ejemplo 1:

![[../Atachments/Pasted image 20250829165501.png]]

Ejemplo 2:

![[../Atachments/Pasted image 20250829165609.png]]

### Operador División

Sean r(R) y s(S) relaciones con S contenido en R. La operación r ÷ s es una relación de esquema R-S. Donde: 
• Una tupla t contenido en r ÷ s si para cada tupla ts en s existe una tupla tr en r que satisface las siguientes condiciones:

![[../Atachments/Pasted image 20250829165818.png]]

Observación: la operación de división se define en términos de las operaciones fundamentales como:

![[../Atachments/Pasted image 20250829165845.png]]

Ejemplo 1:

![[../Atachments/Pasted image 20250829165932.png]]

Ejemplo 2:

Número de las carreras que se corrieron en agosto.

![[../Atachments/Pasted image 20250829165959.png]]

### Operador Asignación

El operador asignación provee un medio conveniente para expresar consultas complejas.

![[../Atachments/Pasted image 20250829170218.png]]

• El resultado de la derecha de <-  se asigna a la la variable a la izquierda del operador de asignación. 
• La variable se puede usar en próximas expresiones.

Ejemplo: 
Recuperar los caballos que corrieron todas las carreras que se corrieron en el mes de agosto.

![[../Atachments/Pasted image 20250829170312.png]]

## Otras operaciones del lenguaje de manipulación de datos

• Las operaciones hasta ahora vistas permiten consultar los datos almacenados en una Base de Datos relacional. 
• El grupo de operaciones que veremos a continuación permiten “actualizar” el contenido de la Base de Datos, fundamentalmente por medio de las operaciones de: 
• inserción, borrado y actualización.

### Eliminación

Consiste en borrar o eliminar tuplas de una relación. 
Notación: r <- r - E. 

Ejemplo: 
Eliminar las tuplas de corre con nro-carrera CC-02.

![[../Atachments/Pasted image 20250829170559.png]]

### Inserción

Consiste en agregar o insertar nuevas tuplas a una relación.
Notación: r <- r union E.

Ejemplo: 
Agregar el caballo “Yago” con número CB-07 de 6 años y 240 kilos.

![[../Atachments/Pasted image 20250829170715.png]]

### Modificación

Consiste en modificar datos de una o más tuplas a una relación.
Notación:
![[../Atachments/Pasted image 20250829170755.png]]

Ejemplo: 
Aumentar en 1 las edades de todos los caballos.

![[../Atachments/Pasted image 20250829170815.png]]

