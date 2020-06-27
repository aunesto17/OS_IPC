#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

//nombre con el cual vamos a acceder a la semafora
#define SEM_PATH     "/sem_OS"
#define MTX_PATH     "/sem_M"

int main(int argc, char *argv[]) {
    //sem_open(nombre, abrir o crear, permisos, recursos para la semafora)
    sem_t * sem_id1 = sem_open(SEM_PATH, O_CREAT, S_IRUSR | S_IWUSR, 0);
    // semafora del mutex
    sem_t * sem_id2 = sem_open(MTX_PATH, O_CREAT, S_IRUSR | S_IWUSR, 0); 
    return 0;
}
