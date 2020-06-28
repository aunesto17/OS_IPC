#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 128
#define SHMSZ 1000


int main()
{
    // FIFO variables
    int fd;
    char * myfifo = "/tmp/myfifo";
    char buf[MAX_BUF];

    // shm variables
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    // shm key
    key = 1234;

    /* open, read, and display the message from the FIFO */
    fd = open(myfifo, O_RDONLY);
    read(fd, buf, MAX_BUF);
    printf("Recibido: %s\n", buf);
    close(fd);

    // creamos el segmento del shm
    if ((shmid = shmget(key,MAX_BUF , IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // unimos el segmento a nuestro espacio
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    s = shm;
    // copiamos el buffer a la shm
    strncpy(s, buf, MAX_BUF);
    *s = NULL;

    while (*shm != '*')
        sleep(1);

    return 0;
}
