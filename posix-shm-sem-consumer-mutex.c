#include <stdio.h> 
#include <stdlib.h> 
#include <sys/mman.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <semaphore.h>

#define SEM_PATH "/sem_OS"
#define SEM_MTX  "/sem_M"

void forkChildren (int nChildren) {
    int i;
    pid_t pid;
    for (i = 1; i <= nChildren; i++) {
        pid = fork();
        if (pid == -1) {
            /* error handling here, if needed */
            return;
        }
        if (pid == 0) {
            printf("Proceso %d comenzando PID: %d\n",i, getpid());
            sleep (1);
            return;
        }
    }
}


int main() 
{
    pid_t parent = getpid(); 
    printf("Proceso Padre: %d\n", parent);
    forkChildren(6);
    pid_t child = getpid();
    /* the size (in bytes) of shared memory object */
    const int SIZE = sizeof(int);

    /* name of the shared memory object */
    const char* name = "OS"; 

    /* shared memory file descriptor */
    int shm_fd; 

    /* pointer to shared memory object */
    void* ptr; 

    /* open the shared memory object */
    shm_fd = shm_open(name, O_RDWR, 0666); 

    /* memory map the shared memory object */
    int * data = (int*) mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    // abrimos la semafora consumer
    sem_t * sem_id = sem_open(SEM_PATH, O_CREAT , S_IRUSR | S_IWUSR, 0);
    // wait for resources
    sem_wait(sem_id);
    printf("Semafora abierta.. \n");
    printf("Numero en la SM: %d ,aumentando en 1.\n", *data);
    data = (int*) mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    // abrimos el mutex
    sem_t * mutex = sem_open(SEM_MTX, O_CREAT, S_IRUSR | S_IWUSR, 0);
    // ejecutamos la operacion
    sem_wait(mutex);
    *data = *data + 1;
    sem_post(mutex);

    printf("Data: %d\n", *data);
    // sem post to resources
    sem_post(sem_id);
    printf("Posteando en la semafora.. \n");

    printf("proceso %d ejecutado.. \n",getpid());

    /* read from the shared memory object */
    munmap(data, SIZE);
    close(shm_fd);
    /* remove the shared memory object */
    //if (child == parent+6)
        //shm_unlink(name);
    return 0; 
} 
