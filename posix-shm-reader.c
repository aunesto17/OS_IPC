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

    /* shared memory file descriptor */
    int shm_fd; 

    /* open the shared memory object */
    shm_fd = shm_open(name, O_RDONLY, 0666); 

    /* memory map the shared memory object */
    int * data = (int*) mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    printf("reciever mapped address: %p\n", data); 

    /* read from the shared memory object */
    printf("%d\n", *data);
    munmap(data, SIZE);
    close(shm_fd);

    /* remove the shared memory object */
    shm_unlink(name); 
    return 0; 
} 
