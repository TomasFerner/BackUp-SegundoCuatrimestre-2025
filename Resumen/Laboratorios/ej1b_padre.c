#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define SHM_NAME "/contador_letras"

typedef struct {
    int total_count;
    int processed_files;
} shared_data_t;

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Uso: %s archivo1 archivo2 archivo3 [archivo4 ...]\n", argv[0]);
        printf("Debe especificar al menos 3 archivos\n");
        return 1;
    }
    
    int num_files = argc - 1;
    
    // Crear memoria compartida
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }
    
    if (ftruncate(shm_fd, sizeof(shared_data_t)) == -1) {
        perror("ftruncate");
        return 1;
    }
    
    shared_data_t *shared_data = mmap(0, sizeof(shared_data_t), 
                                      PROT_READ | PROT_WRITE, 
                                      MAP_SHARED, shm_fd, 0);
    if (shared_data == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
    
    // Inicializar datos compartidos
    shared_data->total_count = 0;
    shared_data->processed_files = 0;
    
    printf("Procesando %d archivos...\n", num_files);
    
    // Crear procesos hijos
    for (int i = 0; i < num_files; i++) {
        pid_t pid = fork();
        
        if (pid == 0) {
            // Proceso hijo - ejecutar el programa hijo
            char *args[] = {"./ej1b_hijo", argv[i + 1], NULL};
            execv("./ej1b_hijo", args);
            perror("execv");
            exit(1);
        } else if (pid < 0) {
            perror("fork");
            return 1;
        }
    }
    
    // Esperar a que terminen todos los hijos
    for (int i = 0; i < num_files; i++) {
        wait(NULL);
    }
    
    // Leer resultado final
    printf("==========================================\n");
    printf("Procesamiento completado!\n");
    printf("Total de apariciones de 'a' y 'A': %d\n", shared_data->total_count);
    printf("Archivos procesados: %d\n", shared_data->processed_files);
    printf("==========================================\n");
    
    // Limpiar memoria compartida
    munmap(shared_data, sizeof(shared_data_t));
    close(shm_fd);
    shm_unlink(SHM_NAME);
    
    return 0;
}