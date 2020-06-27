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
    sem_t * sem_id = sem_open(SEM_PATH, O_CREAT, S_IRUSR | S_IWUSR, 7);
    int i;
    // operacion que incrementa la semafora
    while (1){
        printf("Posteando 7 recursos en la semafora en 5 seg...\n");
        sleep(5);
        for(i=0;i<7;i++){
            sem_post(sem_id);
        }
        i=0;
    }
    return 0;
}
