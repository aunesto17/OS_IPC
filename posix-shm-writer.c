#include <stdio.h> 
#include <stdlib.h> 
#include <sys/mman.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <semaphore.h>

int main() 
{ 
    /* the size (in bytes) of shared memory object */
    const int SIZE = sizeof(int);

    /* name of the shared memory object */
    const char* name = "OS"; 

    /* strings written to shared memory */
    //const char* message_0 = "Hello"; 
    //const char* message_1 = "World!"; 

    /* shared memory file descriptor */
    int shm_fd; 

    /* pointer to shared memory obect */
    //void* ptr; 

    /* create the shared memory object */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); 

    /* configure the size of the shared memory object */
    ftruncate(shm_fd, SIZE); 

    /* memory map the shared memory object */
    int * data = (int*) mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    printf("sender mapped address: %p\n",data);

    /* write to the shared memory object */

    *data = 1;

    munmap(data, SIZE);
    close(shm_fd);

    return 0; 
}
