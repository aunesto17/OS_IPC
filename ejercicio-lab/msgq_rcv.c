#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAXSIZE     128

void die(char *s)
{
  perror(s);
  exit(1);
}

struct msgbuf
{
    long    mtype;
    char    mtext[MAXSIZE];
};


void main()
{
    // msq variables
    int msqid;
    struct msgbuf rcvbuffer;
    size_t buflen;

    key_t key;

    // key para todos los procesos
    key = 1234;

    // msq recieve
    if ((msqid = msgget(key, 0666)) < 0)
      die("msgget()");

    if (msgrcv(msqid, &rcvbuffer, MAXSIZE, 1, 0) < 0)
      die("msgrcv");

    // manejamos el bufer
    printf("Mensaje recibido: %s\n", rcvbuffer.mtext);

    // creamos la pipe FIFO
    int fd;
    char * myfifo = "/tmp/myfifo";

    mkfifo(myfifo, 0666);

    // pasamos el buffer al FIFO
    fd = open(myfifo, O_WRONLY);
    write(fd, rcvbuffer.mtext, MAXSIZE);
    close(fd);

    /* remove the FIFO */
    unlink(myfifo);

    exit(0);
}

