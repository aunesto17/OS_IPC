#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

//nombre con el cual vamos a acceder a la semafora
#define SEM_PATH     "/sem_OS"

int main(int argc, char *argv[]) {
    //sem_open(nombre, abrir o crear, permisos, recursos para la semafora)
    sem_t * sem_id = sem_open(SEM_PATH, O_CREAT, S_IRUSR | S_IWUSR, 5);

    return 0;
}
