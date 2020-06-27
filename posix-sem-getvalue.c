
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

    // nos retorna el valor de la semafora
    sem_t * sem_id = sem_open(SEM_PATH, O_CREAT , 0777,0); 
    int *sval;
    // obtengo el valor de esa semafora
    sem_getvalue(sem_id, sval);
    printf("value of the semaphore: %d\n",*sval);

    return 0;
}

