/*
1. El código en cuenta.c (disponible en moodle) recibe un archivo de entrada y cuenta la cantidad de apariciones
 de la letra 'a' o 'A' en el mismo. Modifique el archivo para que:

b)

El usuario pueda indicar más de un archivo de entrada (por lo menos 3).
Se deben crear tantos procesos como archivos ingresados. Se debe procesar en paralelo cada archivo.
Los resultados deben actualizarse en una variable compartida, que mantiene la suma total, ubicada en un segmento de memoria compartida.
El padre debe leer el resultado y mostrarlo por pantalla.
Implementar código del padre e hijos en archivos separados. El padre ejecuta cada hijo mediante execv.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

#define SHM_NAME "/contador_letras"
#define SEM_NAME "/sem_contador"

typedef struct {
    int total_count;
    int processed_files;
} shared_data_t;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s archivo\n", argv[0]);
        return 1;
    }
    
    char *filename = argv[1];
    
    // Abrir archivo para leer
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: No se puede abrir el archivo %s\n", filename);
        return 1;
    }
    
    // Contar apariciones de 'a' y 'A'
    int count = 0;
    int c;
    
    while ((c = fgetc(file)) != EOF) {
        if (c == 'a' || c == 'A') {
            count++;
        }
    }
    
    fclose(file);
    
    // Acceder a memoria compartida
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }
    
    shared_data_t *shared_data = mmap(0, sizeof(shared_data_t), 
                                      PROT_READ | PROT_WRITE, 
                                      MAP_SHARED, shm_fd, 0);
    if (shared_data == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
    
    // Crear/abrir semáforo para sincronización
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }
    
    // Sección crítica - actualizar datos compartidos
    sem_wait(sem);
    shared_data->total_count += count;
    shared_data->processed_files++;
    printf("Archivo %s: %d apariciones (PID: %d)\n", filename, count, getpid());
    sem_post(sem);
    
    // Limpiar recursos
    sem_close(sem);
    munmap(shared_data, sizeof(shared_data_t));
    close(shm_fd);
    
    return 0;
}