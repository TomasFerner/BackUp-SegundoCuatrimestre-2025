## ¿Qué es Alloy?

Alloy es un lenguaje de **modelado declarativo**.  
No se programa "qué hacer", sino que se describe **qué es cierto** sobre un modelo, y luego la herramienta (Alloy Analyzer) genera **ejemplos posibles (instancias)** que cumplen esas condiciones.

- **sig** = _signature_ → sirve para declarar un conjunto de elementos (como un tipo o clase).
- Cada `sig` define un conjunto **finito** de átomos (elementos indivisibles).  
    Ej: `sig T {}` significa: “existe un conjunto llamado T con algunos elementos (que Alloy inventa)”.

Cuando le das a _run_ en el Alloy Analyzer, este te genera **instancias gráficas** de esos conjuntos y relaciones.


## El modelo base

Tenemos por ejemplo:

`sig T {} y sig U {}`

- `T` y `U` son conjuntos (tipos).
- Pueden estar vacíos o tener varios elementos (depende de lo que Alloy elija en cada corrida, salvo que pongas restricciones).

Después tenemos varias versiones de:

`sig S { r: ... }`

Es decir, una signatura `S` con un campo `r`.  
Ese campo es **una relación** entre `S` y lo que pongamos a la derecha

En Alloy, al declarar un campo, podés indicar **cuántos elementos puede tener** esa relación. Algunas multiplicidades son:

- `lone` → cero o uno.
- `one` → exactamente uno.
- `some` → uno o más.
- `set` → cualquier cantidad (cero, uno o muchos).

Y si ves cosas como `T -> one U`, significa: **una relación binaria** entre `T` y `U`, con la restricción de multiplicidad sobre el lado de `U`.

## Ahora caso por caso del trabajo practico 2

### a) `sig S { r: lone T }`

- `r` es una relación que para cada elemento de `S` apunta a **cero o un elemento de T**.   
- Ejemplo válido:
    - `S = {s1, s2}`
    - `T = {t1, t2}`
    - `r = { s1 → t1 }` (s2 no apunta a nada).
- Ejemplo inválido:
    - `r = { s1 → t1, s1 → t2 }` → porque `s1` no puede tener más de un `T`.
### b) `sig S { r: one T }`

- Cada `S` debe estar relacionado con **exactamente un T**.
- Ejemplo válido:
    - `S = {s1, s2}`, `T = {t1, t2}`
    - `r = { s1 → t1, s2 → t2 }`.
- Ejemplo inválido
    - `r = { s1 → t1 }` (si `s2` existe, debe tener un `T`).
    - O también si `r = { s1 → t1, s1 → t2 }`.
### c) `sig S { r: T -> one U }`

- `r` es una relación ternaria: conecta un `S` con un par `(T,U)`.
- Para cada par `(s,t)` hay **exactamente un `U`**.
- Ejemplo válido:
    - `S = {s1}`, `T = {t1,t2}`, `U = {u1,u2}`
    - `r = { (s1,t1) → u1, (s1,t2) → u2 }`.
- Ejemplo inválido:
    - `(s1,t1) → u1, (s1,t1) → u2` → no se puede porque debe ser “uno”.
    - O si algún `(s,t)` no apunta a nada.
### d) `sig S { r: T lone -> U }`

- Aquí, desde cada `(s,u)` puede haber relación con **cero o un T**.
- Lo que cambia es la restricción: el lado de T está limitado a “lone”.
- Ejemplo válido:
    - `r = { (s1,u1) → t1 }` o vacío.
- Ejemplo inválido
    - `r = { (s1,u1) → t1, (s1,u1) → t2 }`.
### e) `sig S { r: some T }`

- Cada `S` debe estar relacionado con **uno o más `T`**.
- Ejemplo válido:
    - `S = {s1}`, `T = {t1,t2}`
    - `r = { s1 → t1, s1 → t2 }`.
- Ejemplo inválido:
    - `r = {}` (porque tiene que haber “al menos uno”).
### f) `sig S { r: set T }`

- Relación totalmente libre: cada `S` puede tener cero, uno o muchos `T`.
- Ejemplo válido: cualquiera.
- Ejemplo inválido: **ninguno**, porque `set` no impone restricciones.
### g) `sig S { r: T set -> set U }`

- Relación ternaria: `(s,t,u)`.
- “set” en ambos lados → sin restricciones.
- Ejemplo válido: cualquier cosa.
- Ejemplo inválido: no hay, porque es completamente libre.
### h) `sig S { r: T one -> U }`

- Para cada `(s,u)` debe haber **exactamente un `T`**.
- Ejemplo válido:
    - `S = {s1}`, `T = {t1}`, `U = {u1,u2}`
    - `r = { (s1,u1) → t1, (s1,u2) → t1 }`.
- Ejemplo inválido:
    - `(s1,u1) → t1, (s1,u1) → t2` (más de un `T`).
    - O si falta un `T` para algún `(s,u)`.

