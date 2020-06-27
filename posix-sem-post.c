#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>


#define SEM_PATH     "/sem_OS"

int main(int argc, char *argv[]) {
    // abrimos la semafora
    sem_t * sem_id = sem_open(SEM_PATH, O_CREAT, S_IRUSR | S_IWUSR, 3);
    // operacion que incrementa la semafora
    sem_post(sem_id);

     return 0;
}
