Conceptos MER:
[[Clase Introducción a la Materia 19-8]]
## Pasaje a tablas
→Es posible traducir el diseño conceptual del Diagrama Entidad Relación (DER) a una representación lógica como un grupo de tablas. 
→El proceso de conversión se conoce informalmente como “pasaje a Tablas del DER
### Entidades Fuertes

- Se crea una tabla para E que constará de n columnas, una por cada atributo. 
- A cada atributo se le define su dominio.
- Cada fila de la tabla es una entidad del conjunto entidad E. 
-  Los atributos llave primaria de E son la llave primaria de la tabla de E.

![[../Atachments/Pasted image 20250822175431.png]]

![[../Atachments/Pasted image 20250822175448.png]]

### Entidades Débil

Sea A un conjunto entidad débil con n atributos descriptivos a1 ,a2 ,…,an . 
 Sean los atributos a1 ,a2 ,…,an los discriminadores del conjunto A. 
 Sea B el conjunto entidad fuerte que domina a A con atributos b1 ,b2 ,…,bm , y sea b1 ,b2 ,…,bj los atributos que forman la llave primaria para B 
 La “estructura” de la tabla para la entidad débil A constará de n+j columnas:

![[../Atachments/Pasted image 20250822175608.png]]

![[../Atachments/Pasted image 20250822175630.png]]

### Atributos Especiales
atributos derivados, atributos compuestos, atributos multivalorados

![[../Atachments/Pasted image 20250822175952.png]]

### Conjuntos Relación

![[../Atachments/Pasted image 20250822180100.png]]

#### Conjunto relación sin atributos

![[../Atachments/Pasted image 20250822180156.png]]
notar que la relación se subraya por usar una llave con isbn y dni simultáneamente, esto ya que un libro si bien tiene un isbn único puede tener varios autores, la llave se utiliza para encontrar la fila exacta para rescatar la información necesaria a traves de la relación, por eso usamos el dni tambien como dato
#### Conjunto relación con atributos

![[../Atachments/Pasted image 20250822180250.png]]


### Conjunto de relaciones

#### 1:m
![[../Atachments/Pasted image 20250822181142.png]]

#### 1:1
![[../Atachments/Pasted image 20250822181157.png]]

### Traducción a tabla de la relación ES-UN
1. Se crea una tabla para el conjunto de entidades de nivel más alto. 
2. Para cada conjunto de entidades de nivel más bajo se crea una tabla con los atributos de ese conjunto de entidades más una columna por cada atributo que es clave primaria del conjunto de entidades de nivel más alto. • Esta opción es válida para generalizaciones solapadas o disjuntas y parciales o totales.

Ejemplo 1:
	P(**a1**,a2,a3)
	h1(**a1**,b1)
	h2(**a1**,c1,c2)

Ejemplo 2 Grafico:

MER
![[../Atachments/Pasted image 20250822181556.png]]

Tablas
![[../Atachments/Pasted image 20250822181614.png]]

### Traducción a tabla de relación de agregación

La transformación de una relación de agregación es directa, respetando las mismas reglas vistas.

Ejemplo 1: 
	consideremos que se necesitan tablas para las entidades fuertes: 
	- **Empleado**
	- **Proyecto** 
	- **Maquinaria**
	Y sean las relaciones: 
	- **Trabaja**
	- **Usa**: incluye una columna para cada atributo en la clave primaria del conjunto de entidades **maquinaria** y para cada atributo de la clave primaria de **trabaja**.

Ejemplo 2:

MER
![[../Atachments/Pasted image 20250822182002.png]]

Entidades y Relaciones:
![[../Atachments/Pasted image 20250822182248.png]]
**en las relaciones los atributos llave son los atributos subrayados**
**en las entidades los atributos fuertes son los subrayados**
