
## Esquema de Relación y Relación

==Los esquemas de relacion son un buen disenio solo si la unica dependencia funcional es que el atributo llave defina a todos los atributos==

Un esquema de relación R es un conjunto finito de nombres de atributos {A1 ,…,An} tal que:'
• A cada atributo Ai se le asocia un dominio dom(Ai ). 
• Los nombres de los atributos se denominan símbolos de atributos o simplemente atributos.

Una relación r sobre un esquema de relación R, r(R), 
es un conjunto finito de mapeos o tuplas {t1 ,…,tp} de R a D, con D = dom(Ai ) x...x dom(An) tal que si una tupla t pertenece a r entonces t(Ai) debe pertenecer a dom(Ai).

![[../Atachments/Pasted image 20250902144044.png]]

### Notación

![[../Atachments/Pasted image 20250902144206.png]]

## Dependencias Funcionales


Sea R (A1 ,… , An ) un esquema de relación, X e Y subconjuntos de atributos {A1 ,… , An }.
Se dice  **"X determina funcionalmente a Y"** o que **"Y depende funcionalmente de X"** si para cualquier relación r sobre el esquema de relación R (r(R))
no es posible que en r existan dos o más tuplas que coincidan en todos los valores de X, pero no coinciden en uno o más componentes de Y:
![[../Atachments/Pasted image 20250902144448.png]]

Una dependencia funcional (df) es un tipo de restricción que se fija y que deben satisfacer todas las relaciones r(R)

Notación: X -> Y

### Satisfacibilidad

Propiedad: Satisfacibilidad Las dependencias funcionales se definen sobre el esquema R, y para ser satisfechas por todas las instancias r(R).

Formalmente, una relación r satisface la df X → Y si para cualquier par de tuplas t1 y t2 en r vale que:

![[../Atachments/Pasted image 20250902144743.png]]

![[../Atachments/Pasted image 20250902144811.png]]

### Ejemplo:

Sean los atributos M (Materia), P (Profesor), H (Día-Hora), A (Aula), E (Estudiante) definidos en R (MPHAE) 
Sobre R se definen las siguientes dependencias funcionales:
	• HA → M Un horario y aula una única materia. 
	• HP → AM Un profesor en un horario está dando clases en una única aula y de una única materia. 
	• HE → A Un alumno en un horario está en un aula. 
	• EM → P Un estudiante y una materia la cursa con un único profesor.

![[../Atachments/Pasted image 20250902144911.png]]

Sea R(A1 ,… ,An ) un esquema de relación y X una llave candidata para R, entonces la dependencia funcional X→ Ai es verdadera para todo atributo Ai de R.

### Resumen

![[../Atachments/Pasted image 20250902150155.png]]

### Implicancia

Dado F, el conjunto de dependencias funcionales o restricciones para R, se dice que 
F implica lógicamente X → Y ó F |= { X → Y }

Si se cumple que siempre que si en r se satisface F, entonces en r también se satisface X → Y. Ejemplo: R (ABC) y F = {A → B, B → C} ⊨ A → C.

A todas las df’s lógicamente implicadas por F se denomina clausura de F ó F +
### Axiomas de Armstrong

![[../Atachments/Pasted image 20250902151308.png]]

Reglas de Inferencia (deducen nuevos conocimientos) 
1. Unión: {X → Y, X → Z} |= X → YZ. 
2. Pseudotransitividad: {X → Y, WY → Z} |= WX → Z. 
3. Descomposición: Si X → Y y Z contenido Y entonces X → Z.

### Clausura de Atributos (X+)

Dados R y F; sea X contenido R un conjunto de atributos de R se define como clausura de X bajo F (y se nota X + F ) al conjunto de todos los atributos funcionalmente determinados por X bajo F. 

![[../Atachments/Pasted image 20250902160439.png]]

### ¿Cómo calcular X+?

![[../Atachments/Pasted image 20250902160545.png]]

Ejemplo

![[../Atachments/Pasted image 20250902160559.png]]

Si tengo (bd)+ sub f, 
la forma fácil  es ir iterando sobre f en todas las implicaciones mirando a la izquierda de todos los elementos de f, si esta contenido en este caso en bd, lo agregamos al resultado, y actualizamos, esto es ahora chequear si la union de bd con las nuevas letras encontramos nuevas letras que agregar a través de las implicaciones
### Conceptos Metateóricos en el Modelo Relacional

• Sensatez (Soundness): Una teoría formal T es sensata si todo lo que se demuestra en T es verdadero en todas las interpretaciones.

• Completitud (Completeness): Una teoría formal T es completa si todo lo que es verdadero en todas las interpretaciones es demostrable en T. 

• Teorema: Los axiomas de Armstrong son sensatos y completos.

