#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Declaración de variables booleanas
bool esValido = true;
bool activo = false;

// Declaración de variables enteras
int numero = 10;
int contador = 0;

//Declaracion de variables char
char caracter = 'A';
char cadena[] = "Hola, Mundo!";

// Función que genera 5 caracteres aleatorios
void generarCaracteresAleatorios(char caracteres[]) {
    for (int i = 0; i < 5; i++) {
        caracteres[i] = 'A' + rand() % 26; // Genera letras mayúsculas aleatorias (A-Z)
    }
    caracteres[5] = '\0'; // Terminar la cadena
}

// Función que genera 5 números aleatorios
void generarNumerosAleatorios(int numeros[]) {
    for (int i = 0; i < 5; i++) {
        numeros[i] = rand() % 100; // Genera números entre 0 y 99
    }
}

int main() {
    // Inicializar generador de números aleatorios
    srand(time(NULL));
    
    printf("=== Variables Booleanas ===\n");
    printf("esValido: %d\n", esValido);
    printf("activo: %d\n", activo);

    printf("\n=== Variables Enteras ===\n");
    printf("numero: %d\n", numero);
    printf("contador: %d\n", contador);

    printf("\n=== Variables de Caracter ===\n");
    printf("caracter: %c\n", caracter);
    printf("cadena: %s\n", cadena);

    // Arrays para almacenar valores aleatorios
    char caracteresAleatorios[6]; // 5 caracteres + terminador nulo
    int numerosAleatorios[5];

    // Generar valores aleatorios
    generarCaracteresAleatorios(caracteresAleatorios);
    generarNumerosAleatorios(numerosAleatorios);

    printf("\n=== Valores Aleatorios ===\n");
    printf("Caracteres aleatorios: %s\n", caracteresAleatorios);
    printf("Números aleatorios: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numerosAleatorios[i]);
    }
    printf("\n");

    return 0;
}

