## Los mundos de los sistemas de bases de datos

**Importancia de las bases de datos**:  
    Hoy en día son fundamentales para empresas, sitios web (Google, Amazon, etc.) y también en la ciencia (astronomía, genómica, bioquímica).

**DBMS (Database Management System)**:  
    Un sistema especializado que permite crear, administrar y mantener grandes volúmenes de datos de manera eficiente, segura y persistente.  
    Sus principales funciones son:
    1. Definir esquemas (estructura lógica de los datos).
    2. Permitir consultas y modificaciones con lenguajes especializados.
    3. Manejar grandes volúmenes de datos de forma eficiente.
    4. Garantizar durabilidad y recuperación frente a fallos.
    5. Controlar acceso concurrente asegurando aislamiento y atomicidad.
#### Evolución de los sistemas de bases de datos

**Primeros DBMS (años 60s–70s)**
    - Derivaban de los sistemas de archivos, pero estos tenían limitaciones: sin consultas complejas, sin garantía de durabilidad, ni control de concurrencia.    
    - Aplicaciones clave: banca, reservas aéreas, registros corporativos.
    - Modelos usados: jerárquico y de red (CODASYL).
    - Problema: no existían lenguajes de consulta de alto nivel, las consultas eran complejas de programar.
**Modelo relacional (Ted Codd, 1970)**
    - Organiza datos en **tablas (relaciones)**.
    - Separa la vista lógica del usuario de la estructura física de almacenamiento        
    - Introducción de **SQL** como lenguaje de consultas de alto nivel.
    - Para los 90s, los sistemas relacionales eran el estándar.
**Tendencias modernas**
    - Incorporación de características **orientadas a objetos**.
    - Aparición de sistemas alternativos para manejar bases de datos muy grandes
    - Miniaturización: DBMS en **PCs y dispositivos pequeños** (antes solo en grandes servidores).
    - Uso de documentos (ej. **XML**) como forma de organizar datos.
## Capítulo 1 – Los mundos de los sistemas de bases de datos (continuación)

#### **1.1.4 Bases de datos cada vez más grandes**

- Hoy las bases de datos alcanzan tamaños de **terabytes y petabytes**.
- Ejemplos:
    1. Google: petabytes de datos de la Web en estructuras optimizadas para búsquedas.
    2. Satélites: generan enormes volúmenes de información.
    3. Imágenes: repositorios como Flickr o Amazon con millones de fotos.
    4. Videos: sitios como YouTube almacenan millones de películas.
    5. Redes P2P: distribuyen enormes cantidades de datos en computadoras comunes.

#### **1.1.5 Integración de información**

- Problema actual: **unificar datos dispersos en múltiples bases de datos** (de diferentes divisiones, empresas adquiridas, con distintos DBMS y estructuras).
- Dificultades: términos distintos para lo mismo, mismo término para cosas diferentes, y aplicaciones heredadas que no pueden eliminarse.
- Soluciones:
    - **Data warehouses**: copiar y transformar periódicamente datos a una base central.
    - **Mediadores (middleware)**: integran datos de distintos sistemas sin unificarlos físicamente, traduciendo entre modelos.

### **1.2 Visión general de un DBMS**

Un DBMS tiene dos tipos principales de usuarios/comandos:

1. **Usuarios y programas** → hacen consultas o modificaciones.
2. **Administrador de base de datos (DBA)** → define la estructura/esquema.

#### **1.2.1 Lenguaje de definición de datos (DDL)**

- Usado por el **DBA** para crear o modificar el esquema (estructuras, restricciones, tablas, etc.).
- Procesado por el **DDL processor**, que actualiza los metadatos de la base.
#### **1.2.2 Procesamiento de consultas (DML)**

- **Usuarios/programas** usan DML para consultar o modificar datos (no la estructura).
- Flujo
    1. Consulta → **parser + optimizador** → plan de ejecución.
    2. **Execution engine** → solicita datos al resource manager.
    3. **Buffer manager** → mueve páginas desde disco a memoria.
    4. **Storage manager** → coordina acceso al disco.
- **Transacciones**:
    - Unidad de ejecución con propiedades **ACID** (atómicas, aisladas, duraderas).
    - Componentes:
        1. **Concurrency-control manager**: garantiza atomicidad y aislamiento.
        2. **Logging & recovery manager**: asegura durabilidad frente a fallos.

#### **1.2.3 Almacenamiento y manejo de buffers**

- Los datos viven en **almacenamiento secundario** (discos).
- Para operar sobre ellos deben cargarse en **memoria principal**.
- El **storage manager** controla ubicación en disco y movimiento hacia/desde memoria.
- En sistemas simples, esto lo maneja el **file system del SO**, pero en DBMS se usan técnicas más eficientes.

En resumen: además de crecer hacia bases **muy grandes** (petabytes) y la **integración de información dispersa**, el capítulo introduce cómo un DBMS procesa comandos (DDL/DML), cómo organiza el procesamiento de consultas, transacciones y almacenamiento, asegurando siempre las propiedades ACID.