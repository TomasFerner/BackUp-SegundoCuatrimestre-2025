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
- Sean los atributos a1 ,a2 ,…,an los discriminadores del conjunto A. 
- Sea B el conjunto entidad fuerte que domina a A con atributos b1 ,b2 ,…,bm , y sea b1 ,b2 ,…,bj los atributos que forman la llave primaria para B 
-  La “estructura” de la tabla para la entidad débil A constará de n+j columnas:

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

## Atributos Llave para Conjuntos Relación

### Restricciones 
En el modelo de datos de una empresa buscamos expresar ciertas restricciones que garanticen la calidad del contenido de su base de datos. 

Las herramientas que usaremos para expresar las restricciones son: 
1. **Cardinalidad** de Mapeos 
2. **Atributos Llaves** (o claves). 
	•Llave de entidad. 
	• Llave de relación

![[../Atachments/Pasted image 20250826144136.png]]

### Llaves

Se entiende llave como una especie de puntero que te lleva a lo que esta referenciando

**Superllave**: es uno o más atributos del conjunto entidad que distingue unívocamente a un elemento del conjunto de entidad. 
- Nro-Seguridad-Social es superllave del conjunto de entidades Cliente. 
- Nro-Seguridad-Social y Nombre-Cliente es superllave del conjunto de entidades Cliente. 

**Llave Candidata**: es una superllave que no contiene un subconjunto propio que sea superllave. Es decir, es una superllave minima. 

**Llave Primaria**: es una llave candidata elegida por el diseñador de la base de datos.

### Llaves del conjunto relacion

Desde un punto de vista conceptual las relaciones del conjunto relación son distinguibles y las diferencias se expresan en términos de sus atributos.
- **Superllave** del conjunto relación atributo/s que distinguen unívocamente a una relación del conjunto. 
- **Llave candidata** del conjunto relación es una superllave mínima. 
- **Llave primaria** es una llave candidata que el diseñador elige como principal.
### Resumen 
- La llave primaria para un conjunto de relación / conjunto entidad siempre está definida entre sus atributos y es independiente de la instancia en un momento. 
- Conjunto entidad débil (ED), cuya llave es Llave primaria(EF)  Discriminador(ED) 
- Conjunto relación m:n sin atributos propios: se define como la unión de Llave primaria(E) de las entidades que vincula. 
- Conjunto relación m:1 sin atributos propios: se define como la Llave primaria(E) de las entidades que es el muchos en la relación. 
- Conjunto relación 1:1 sin atributos propios: se define como la Llave primaria(E) de cualquiera de las entidades, ambas son llave candidata. 
- Si el conjunto de relación tiene atributos propios la selección de la llave dependerá de la semántica y restricciones que se quieran modelar.

### Llaves Foráneas

Es un tipo de restricción que exige que el valor que está en una relación r debe estar en otra relación s 
• r se denomina Referencing relation 
• s se denomina Referenced relation 
Ejemplo: el valor del atributo {ISBN} en la relación escrito_por debe estar en la relación libro y el valor {ID} en la relación escrito_por debe estar en la relación libro

![[../Atachments/Pasted image 20250826145452.png]]

![[../Atachments/Pasted image 20250826145439.png]]