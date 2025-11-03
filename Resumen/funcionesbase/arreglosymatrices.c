#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 5
#define FILAS 3
#define COLUMNAS 4

// Función que retorna verdadero si encuentra un número específico en la matriz
bool encontrarNumero(int matriz[FILAS][COLUMNAS], int numero) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (matriz[i][j] == numero) {
                return true;
            }
        }
    }
    return false;
}

// Función que verifica si todos los elementos son mayores a un valor
bool todosMayoresQue(int matriz[FILAS][COLUMNAS], int valor) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (matriz[i][j] <= valor) {
                return false;
            }
        }
    }
    return true;
}

// Función que cuenta cuántos elementos cumplen una condición
int contarPares(int matriz[FILAS][COLUMNAS]) {
    int contador = 0;
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (matriz[i][j] % 2 == 0) {
                contador++;
            }
        }
    }
    return contador;
}

// Función SIMPLE de ordenamiento burbuja con explicación paso a paso
void ordenarBurbujaSimple(int arr[], int tamaño) {
    // Bucle exterior: número de pasadas
    for (int i = 0; i < tamaño - 1; i++) {
        printf("--- PASADA %d ---\n", i + 1);
        // Bucle interior: comparaciones en cada pasada
        for (int j = 0; j < tamaño - 1; j++) {
            printf("Paso %d: Comparando %d y %d -> ", j + 1, arr[j], arr[j + 1]);  
            // Si el elemento actual es mayor que el siguiente, los intercambiamos
            if (arr[j] > arr[j + 1]) {
                printf("Intercambio\n");
                
                // Intercambio simple sin función adicional
                int temp = arr[j];     // Guardar el primer número
                arr[j] = arr[j + 1];   // Poner el segundo en la primera posición
                arr[j + 1] = temp;     // Poner el primer número en la segunda posición

            } 
        }
    }
    printf("¡ORDENAMIENTO COMPLETO!\n");
}

// Función para mostrar un arreglo
void mostrarArray(int arr[], int tamaño, const char* titulo) {
    printf("%s", titulo);
    for (int i = 0; i < tamaño; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    // Declaración e inicialización de array (desordenado para mostrar el ordenamiento)
    int array[ARRAY_SIZE] = {50, 10, 40, 20, 30};
    
    // Declaración e inicialización de matriz
    int matriz[FILAS][COLUMNAS] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    printf("=== RECORRIDO DEL ARRAY ===\n");
    printf("Array de %d elementos:\n", ARRAY_SIZE);
    
    // Recorrido del array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("array[%d] = %d\n", i, array[i]);
    }
    
    printf("\n=== RECORRIDO DE LA MATRIZ ===\n");
    printf("Matriz de %dx%d:\n", FILAS, COLUMNAS);
    
    // Recorrido de la matriz por filas y columnas
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            printf("%4d ", matriz[i][j]);
        }
        printf("\n");
    }
    
    printf("\n=== RECORRIDO DETALLADO DE LA MATRIZ ===\n");
    // Recorrido detallado mostrando índices
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            printf("matriz[%d][%d] = %d\n", i, j, matriz[i][j]);
        }
    }
    
    printf("\n=== SUMA DE ELEMENTOS ===\n");
    
    // Suma elementos del array
    int sumaArray = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sumaArray = sumaArray + array[i];
    }
    printf("Suma del array: %d\n", sumaArray);
    
    // Suma elementos de la matriz
    int sumaMatriz = 0;
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            sumaMatriz = sumaMatriz + matriz[i][j];
        }
    }
    printf("Suma de la matriz: %d\n", sumaMatriz);
    
    printf("\n=== BÚSQUEDA EN LA MATRIZ CON BREAK ===\n");
    
    // Búsqueda de un número específico con break
    int numeroBuscado = 7;
    bool encontrado = false;
    printf("Buscando el número %d en la matriz:\n", numeroBuscado);
    
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            printf("Verificando matriz[%d][%d] = %d\n", i, j, matriz[i][j]);
            if (matriz[i][j] == numeroBuscado) {
                printf("¡Encontrado! El número %d está en la posición [%d][%d]\n", numeroBuscado, i, j);
                encontrado = true;
                break;
            }
        }
        if (encontrado) {
            break;
        }
    }
    
    if (!encontrado) {
        printf("El número %d no se encontró en la matriz\n", numeroBuscado);
    }
    
    printf("\n=== COMPARACIONES CON CONDICIONES ===\n");
    
    // Buscar números mayores a 8
    printf("Elementos mayores a 8:\n");
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (matriz[i][j] > 8) {
                printf("matriz[%d][%d] = %d es mayor a 8\n", i, j, matriz[i][j]);
            }
        }
    }
    
    printf("\n=== FUNCIONES DE VALIDACIÓN ===\n");
    
    // Usar las funciones creadas
    int numeroABuscar = 10;
    bool existe = encontrarNumero(matriz, numeroABuscar);
    printf("¿Existe el número %d en la matriz? %s\n", numeroABuscar, existe ? "Sí" : "No");
    
    bool todosMayores = todosMayoresQue(matriz, 0);
    printf("¿Todos los elementos son mayores a 0? %s\n", todosMayores ? "Sí" : "No");
    
    int cantidadPares = contarPares(matriz);
    printf("Cantidad de números pares en la matriz: %d\n", cantidadPares);
    
    printf("\n=== ORDENAMIENTO SIMPLE CON BURBUJA ===\n");
    
    // Array simple para demostrar
    int arrayParaOrdenar[5] = {64, 34, 25, 12, 22};
    
    printf("Vamos a ordenar este array de menor a mayor:\n");
    ordenarBurbujaSimple(arrayParaOrdenar, 5);
    
    return 0;
}
