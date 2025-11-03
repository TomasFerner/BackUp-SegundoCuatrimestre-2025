/*
1. Diseñar una solución para contar la frecuencia de una palabra en un archivo de texto. 
El archivo de texto está dividido en N segmentos. 
Cada segmento es procesado por un hilo separado que genera el recuento intermedio para su segmento. 
El proceso principal espera hasta que todos los hilos terminen; 
luego calcula la frecuencia de la palabra dada, basado en la salida de los hilos individuales
*/

//gcc -o ej2 ej2.c -pthread ./ej2 archivo.txt palabra 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define MAX_LINE_LENGTH 1000

// Estructura para pasar datos a cada hilo
typedef struct {
    char *filename;
    char *target_word;
    long start_pos;
    long end_pos;
    int thread_id;
    int count;
} thread_data_t;

// Función para convertir una palabra a minúsculas
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Función que ejecuta cada hilo
void* count_word_in_segment(void* arg) {
    thread_data_t *data = (thread_data_t*)arg;
    FILE *file = fopen(data->filename, "r");
    
    if (!file) {
        fprintf(stderr, "Error: No se pudo abrir el archivo %s\n", data->filename);
        data->count = -1;
        pthread_exit(NULL);
    }
    
    // Posicionarse en el inicio del segmento
    fseek(file, data->start_pos, SEEK_SET);
    
    char word[MAX_WORD_LENGTH];
    char target_lower[MAX_WORD_LENGTH];
    strcpy(target_lower, data->target_word);
    to_lowercase(target_lower);
    
    data->count = 0;
    long current_pos = data->start_pos;
    
    // Leer palabras hasta el final del segmento
    while (current_pos < data->end_pos && 
           fscanf(file, "%99s", word) == 1) {
        
        // Limpiar signos de puntuación
        int len = strlen(word);
        while (len > 0 && !isalnum(word[len-1])) {
            word[len-1] = '\0';
            len--;
        }
        
        // Convertir a minúsculas y comparar
        to_lowercase(word);
        if (strcmp(word, target_lower) == 0) {
            data->count++;
        }
        
        current_pos = ftell(file);
    }
    
    fclose(file);
    printf("Hilo %d: Encontradas %d ocurrencias en el segmento [%ld-%ld]\n", 
           data->thread_id, data->count, data->start_pos, data->end_pos);
    
    pthread_exit(NULL);
}

// Función para obtener el tamaño del archivo
long get_file_size(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return -1;
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    return size;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <archivo> <palabra> <num_hilos>\n", argv[0]);
        return 1;
    }
    
    char *filename = argv[1];
    char *target_word = argv[2];
    int num_threads = atoi(argv[3]);
    
    if (num_threads <= 0) {
        fprintf(stderr, "Error: El número de hilos debe ser mayor que 0\n");
        return 1;
    }
    
    // Obtener tamaño del archivo
    long file_size = get_file_size(filename);
    if (file_size == -1) {
        fprintf(stderr, "Error: No se pudo abrir el archivo %s\n", filename);
        return 1;
    }
    
    printf("Archivo: %s, Tamaño: %ld bytes\n", filename, file_size);
    printf("Buscando palabra: '%s' con %d hilos\n\n", target_word, num_threads);
    
    // Crear arrays para hilos y datos
    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    thread_data_t *thread_data = malloc(num_threads * sizeof(thread_data_t));
    
    if (!threads || !thread_data) {
        fprintf(stderr, "Error: No se pudo asignar memoria\n");
        return 1;
    }
    
    // Calcular segmentos para cada hilo
    long segment_size = file_size / num_threads;
    
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].filename = filename;
        thread_data[i].target_word = target_word;
        thread_data[i].thread_id = i;
        thread_data[i].start_pos = i * segment_size;
        
        if (i == num_threads - 1) {
            // El último hilo procesa hasta el final del archivo
            thread_data[i].end_pos = file_size;
        } else {
            thread_data[i].end_pos = (i + 1) * segment_size;
        }
        
        thread_data[i].count = 0;
    }
    
    // Crear y lanzar hilos
    printf("Creando hilos...\n");
    for (int i = 0; i < num_threads; i++) {
        if (pthread_create(&threads[i], NULL, count_word_in_segment, &thread_data[i]) != 0) {
            fprintf(stderr, "Error: No se pudo crear el hilo %d\n", i);
            return 1;
        }
    }
    
    // Esperar a que todos los hilos terminen
    printf("Esperando a que terminen los hilos...\n\n");
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Calcular el total
    int total_count = 0;
    int errors = 0;
    
    for (int i = 0; i < num_threads; i++) {
        if (thread_data[i].count == -1) {
            errors++;
        } else {
            total_count += thread_data[i].count;
        }
    }
    
    // Mostrar resultados
    printf("\n=== RESULTADOS ===\n");
    if (errors > 0) {
        printf("Advertencia: %d hilos tuvieron errores\n", errors);
    }
    
    printf("Frecuencia total de la palabra '%s': %d\n", target_word, total_count);
    
    // Liberar memoria
    free(threads);
    free(thread_data);
    
    return 0;
}

