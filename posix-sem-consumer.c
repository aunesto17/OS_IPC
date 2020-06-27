
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>


#define SEM_PATH "/sem_OS"


int main(int argc, char *argv[]) {

    sem_t * sem_id = sem_open(SEM_PATH, O_CREAT , 0777,0);
    // consumidor de recursos, o espera a que este disponible un recurso
    sem_wait(sem_id);

    return 0;
}

