#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE     128
#define SHMSZ     27

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
    //key_t keym;
    //key_t keys;
    struct msgbuf rcvbuffer;
    size_t buflen;
    // shm variables
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    // msq recieve
    key = 1234;

    // msq recieve
    if ((msqid = msgget(key, 0666)) < 0)
      die("msgget()");

    if (msgrcv(msqid, &rcvbuffer, MAXSIZE, 1, 0) < 0)
      die("msgrcv");
    // manejamos el bufer
    printf("%s\n", rcvbuffer.mtext);

    //buflen = strlen(rcvbuffer.mtext) + 1;
    //printf("bufflen = %zu", buflen);

    // shm server

    //keys = 5678;
    /*
     * Create the segment.
     */
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    /*
     * Now put some things into the memory for the
     * other process to read.
     */
    s = shm;

    /*
    int i;
    for (i = 0; i < buflen; i++)
    {
        printf(rcvbuffer.mtext[i]);
        *s++ = rcvbuffer.mtext[i];
    }
    */

    strncpy(s,rcvbuffer.mtext, SHMSZ);
    *s = NULL;

    /*
    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = NULL;
    */
    /*
     * Finally, we wait until the other process 
     * changes the first character of our memory
     * to '*', indicating that it has read what 
     * we put there.
     */
    while (*shm != '*')
        sleep(1);

    exit(0);
}

