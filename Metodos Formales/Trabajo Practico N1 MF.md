Temas necesarios:
[[Clase introducción a la Materia 21-8]]
## 1. Indique el tamaño, aridad, dominio y rango de las siguientes relaciones:

a) Name = {(G0), (A0), (A1)} 
	Tamaño: 3
	Aridad:1
	Dominio:{G0,A0,A1}
	Rango: no aplica en relaciones unarias
b) addressBook = {(G0,A0), (G0,A1), (A0,D0), (A1,D1)}
	Tamaño:4
	Aridad:2
	Dominio:{G0,A0,A1}
	Rango:{A0,A1,D0,D1}
c) r1 = {(A0,B0,C0), (A3,B0,C1), (A0,B0,D0), (A3,B1,C1), (A1,B2,C0)} 
	Tamaño: 5
	Aridad: 3
	Dominio:{A0,A1,A3}
	Rango:{C0,C1,D0}
d) r2 = {(A1,B3,C1), (A3,B1,C1), (A0,B0,C0), (A2,B2,D0)} 
	Tamaño:4
	Aridad:3
	Dominio:{A1,A3,A0,A2}
	Rango:{C1,C0,D0}
e) r3 = {(A3,B1,C1)}
	Tamaño:1
	Aridad:3
	Dominio:{A3}
	Rango:{C1}

## 2. Considere las siguientes relaciones y la definición de operadores de conjuntos. Para cada inciso, indique si las operaciones debajo listadas son legales y, en caso de serlo, cual es el resultado de realizar dichas operaciones.

a) 
Target = {(G0), (A0), (A1), (D0), (D1), (D2)} 
Name = {(G0), (A0), (A1)} 
Alias = {(A0), (A1)} 
Group = {(G0)} 
Address = {(D0), (D1), (D2)} 
addressBook = {(G0,A0), (G0,A1), (A0,D0), (A1,D1)} 
- **Alias + Group**
	{(A0), (A1),(G0)} 
- Alias & Target 
	{(A0), (A1)}
- **Name - Alias**
	{(G0}
- **Target - Address** 
	{(G0), (A0), (A1)}
- **Target in Group** 
	Falso no esta contenido target in group
- **addressBook & Group**
	No hay elementos iguales entre los 2 conjuntos (pares vs átomos)
- **Alias in Name** 
	Verdadero los elementos {A0,A1} están incluidos
- **Target = Group + Alias**
	Falso {(G0), (A0), (A1), (D0), (D1), (D2)} =/ {G0, A0, A1}

b)
A = {(A0), (A1), (A2), (A3)} 
B = {(B0), (B1), (B2)} 
C = {(C0), (C1)} 
D = {(D0)} 
r1 = {(A0,B0,C0), (A3,B0,C1), (A0,B0,D0), (A3,B1,C1), (A1,B2,C0)} 
r2 = {(A1,B3,C1), (A3,B1,C1), (A0,B0,C0), (A2,B2,D0)} 
r3 = {(A3,B1,C1)}
- **r2 − r1** 
	**{ (A1,B3,C1), (A2,B2,D0) }**
- **r1 & r2** 
	efectivamente **r1 & r2 = r2 & r1** (conmutativa).
- **A + r1** = **{ (A0), (A1), (A2), (A3), (A0,B0,C0), (A3,B0,C1), (A0,B0,D0), (A3,B1,C1), (A1,B2,C0) }**  
    (unión heterogénea: átomos y 3-tuplas).
- **r3 in r2**:  
	**Verdadero**, r3 esta contenido en r2
- **A − B**: 
	como no comparten elementos, A-B = A =**{(A0),(A1),(A2),(A3)}**.
## 3. Considere los siguientes conjuntos de elementos A y B: 

A = {(A0), (A1), (A2), (A3)} 
B = {(B0), (B1), (B2)} 
Determine si la relación binaria $ri$ definida sobre A y B es funcional, inyectiva, ambas, o ninguna: 
a) **r1** = {(A2,B0), (A1,B1), (A3,B2), (A1,B2)} 
b) **r2** = {(A2,B2), (A1,B1)} 
c) **r3** = {(A0,B2), (A3,B0), (A0,B1)} 
d) **r4** = {(A1,B1)), (A2,B1), (A3,B0), (A0, B0)} 
e) **r5** = {(A2,B0), (A3,B1), (A0,B2)}

a) r1={(A2,B0),(A1,B1),(A3,B2),(A1,B2)}

- **Funcional:** No — A1 aparece con dos imágenes distintas (B1 y B2).
- **Inyectiva:** No — además de no ser funcional, no puede ser inyectiva.  
    → **Ninguna.**

b) r2={(A2,B2),(A1,B1)}
- **Funcional:** Sí — cada elemento de AAA que aparece tiene una única imagen.
- **Inyectiva:** Sí — las imágenes (B2, B1) son distintas.  
    → **Ambas (funcional e inyectiva).**

c) r3={(A0,B2),(A3,B0),(A0,B1)}

- **Funcional:** No — A0A0A0 se asocia a B2 y a B1.
- **Inyectiva:** No — falla la funcionalidad, así que no puede ser inyectiva.  
    → **Ninguna.**

d) r4={(A1,B1),(A2,B1),(A3,B0),(A0,B0)}

- **Funcional:** Sí — cada Ai​ aparece exactamente una vez (única imagen por elemento de AAA).
- **Inyectiva:** No — por ejemplo A1 y A2 tienen la misma imagen B1 (y A0,A3 comparten B0).  
    → **Funcional pero no inyectiva.**

e) r5={(A2,B0),(A3,B1),(A0,B2)}

- **Funcional:** Sí — cada A que aparece tiene una sola imagen.
- **Inyectiva:** Sí — las imágenes (B0, B1, B2) son todas distintas.  
    → **Ambas (funcional e inyectiva).**
## 4. Considere los operadores de union (+), intersección (&) y diferencia (-) de conjuntos.

a) Al aplicar dichos operadores sobre dos relaciones binarias que poseen la propiedad de ser funcionales, el resultado ¿preserva la característica de ser una relación funcional (con respecto a las relaciones originales)? Para aquellos casos en que su respuesta sea negativa, brinde un contraejemplo. 

![[../Atachments/{5BC86F0F-9282-4F86-A0D6-B63046E2AACD}.png]]

b) Al aplicar dichos operadores sobre dos relaciones binarias que poseen la propiedad de ser inyectivas, el resultado ¿preserva la característica de ser una relación inyectiva (con respecto a las relaciones originales)? Para aquellos casos en que su respuesta sea negativa, brinde un contraejemplo. 

![[../Atachments/{8C983AE5-0371-4884-86BB-A3CC2A854A06}.png]]

c) Al aplicar dichos operadores sobre dos relaciones binarias que poseen la propiedad de ser funcionales e inyectivas, el resultado ¿preserva la característica de ser una relación funcional e inyectiva (con respecto a las relaciones originales)? Para aquellos casos en que su respuesta sea negativa, brinde un contraejemplo.

![[../Atachments/{D4336EE6-0068-412B-86AC-77087107A44F}.png]]

![[../Atachments/{2B7E0127-EE42-484E-8526-50E1A7F14E52}.png]]

