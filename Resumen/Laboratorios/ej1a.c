/*
1. El código en cuenta.c (disponible en moodle) recibe un archivo de entrada y cuenta la cantidad de apariciones de la letra 'a' o 'A' en el mismo. Modifique el archivo para que:

a)

El usuario pueda indicar más de un archivo de entrada (por lo menos 3).

Se deben crear tantos hilos como archivos ingresados. Los hilos deben procesar en paralelo cada archivo.

Los resultados deben guardarse en un archivo salida.txt compartido por todos los hilos. La escritura en el archivo debe ser sincronizada para evitar conflictos.

*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct {
    char *filename;
    int count;
} thread_data_t;

pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;

void* count_letters(void* arg) {
    thread_data_t *data = (thread_data_t*)arg;
    FILE *file = fopen(data->filename, "r");
    
    if (!file) {
        printf("Error: No se puede abrir el archivo %s\n", data->filename);
        data->count = -1;
        return NULL;
    }
    
    int count = 0;
    int c;
    
    while ((c = fgetc(file)) != EOF) {
        if (c == 'a' || c == 'A') {
            count++;
        }
    }
    
    fclose(file);
    data->count = count;
    
    // Escribir resultado al archivo de salida de forma sincronizada
    pthread_mutex_lock(&file_mutex);
    FILE *output = fopen("salida.txt", "a");
    if (output) {
        fprintf(output, "Archivo %s: %d apariciones de 'a' o 'A'\n", 
                data->filename, count);
        fclose(output);
    }
    pthread_mutex_unlock(&file_mutex);
    
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Uso: %s archivo1 archivo2 archivo3 [archivo4 ...]\n", argv[0]);
        printf("Debe especificar al menos 3 archivos\n");
        return 1;
    }
    
    int num_files = argc - 1;
    pthread_t *threads = malloc(num_files * sizeof(pthread_t));
    thread_data_t *thread_data = malloc(num_files * sizeof(thread_data_t));
    
    // Limpiar archivo de salida
    FILE *output = fopen("salida.txt", "w");
    if (output) {
        fprintf(output, "Resultados del conteo de letras 'a' y 'A':\n");
        fprintf(output, "==========================================\n");
        fclose(output);
    }
    
    // Crear hilos
    for (int i = 0; i < num_files; i++) {
        thread_data[i].filename = argv[i + 1];
        thread_data[i].count = 0;
        
        if (pthread_create(&threads[i], NULL, count_letters, &thread_data[i]) != 0) {
            printf("Error creando hilo para archivo %s\n", argv[i + 1]);
            return 1;
        }
    }
    
    // Esperar a que terminen todos los hilos
    int total_count = 0;
    for (int i = 0; i < num_files; i++) {
        pthread_join(threads[i], NULL);
        if (thread_data[i].count >= 0) {
            total_count += thread_data[i].count;
        }
    }
    
    // Escribir total al archivo
    pthread_mutex_lock(&file_mutex);
    FILE *output2 = fopen("salida.txt", "a");
    if (output2) {
        fprintf(output2, "==========================================\n");
        fprintf(output2, "Total general: %d apariciones\n", total_count);
        fclose(output2);
    }
    pthread_mutex_unlock(&file_mutex);
    
    printf("Procesamiento completado. Resultados en salida.txt\n");
    printf("Total de apariciones: %d\n", total_count);
    
    free(threads);
    free(thread_data);
    pthread_mutex_destroy(&file_mutex);
    
    return 0;
}