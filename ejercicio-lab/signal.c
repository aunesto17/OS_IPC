#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#define MAXSIZE 128

//  https://people.cs.pitt.edu/~alanjawi/cs449/code/shell/UnixSignals.htm

/* 
SIGHUP  1   Exit    Hangup
SIGINT  2   Exit    Interrupt
SIGQUIT 3   Core    Quit
SIGILL  4   Core    Illegal Instruction
SIGTRAP 5   Core    Trace/Breakpoint Trap
SIGABRT 6   Core    Abort
SIGEMT  7   Core    Emulation Trap
SIGFPE  8   Core    Arithmetic Exception
SIGKILL 9   Exit    Killed
SIGBUS  10  Core    Bus Error
SIGSEGV 11  Core    Segmentation Fault
SIGSYS  12  Core    Bad System Call
SIGPIPE 13  Exit    Broken Pipe
SIGALRM 14  Exit    Alarm Clock
SIGTERM 15  Exit    Terminated
SIGUSR1 16  Exit    User Signal 1
SIGUSR2 17  Exit    User Signal 2
SIGCHLD 18  Ignore  Child Status
SIGPWR  19  Ignore  Power Fail/Restart
SIGWINCH    20  Ignore  Window Size Change
SIGURG  21  Ignore  Urgent Socket Condition
SIGPOLL 22  Ignore  Socket I/O Possible
SIGSTOP 23  Stop    Stopped (signal)
SIGTSTP 24  Stop    Stopped (user)
SIGCONT 25  Ignore  Continued
SIGTTIN 26  Stop    Stopped (tty input)
SIGTTOU 27  Stop    Stopped (tty output)
SIGVTALRM   28  Exit    Virtual Timer Expired
SIGPROF 29  Exit    Profiling Timer Expired
SIGXCPU 30  Core    CPU time limit exceeded
SIGXFSZ 31  Core    File size limit exceeded
SIGWAITING  32  Ignore  All LWPs blocked
SIGLWP  33  Ignore  Virtual Interprocessor Interrupt for Threads Library
SIGAIO  34  Ignore  Asynchronous I/O
*/

void sighandler(int);

void die(char *s)
{
  perror(s);
  exit(1);
}

struct msgbuf
{
    long mtype;
    char mtext[MAXSIZE];
};

int main () {
    signal(SIGINT, sighandler);

    while(1) {
        printf("Going to sleep for a second...\n");
        sleep(1); 
    }
    return(0);
}

void sighandler(int signum) {
    // abrimos el archivo
    FILE *fp = fopen("ucsp.txt", "r");
    if(fp == NULL) {
    perror("No se puede abrir el archivo.");
    exit(1);
    }

    char *line = NULL;
    size_t len = 0;

    // creamos el msg queue
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    struct msgbuf sbuf;
    size_t buflen;

    sbuf.mtype = 1;

    // llave para el msgq
    key = 1234;

    if ((msqid = msgget(key, msgflg )) < 0)
      die("msgget");

    // leemos cada linea del archivo
    while(getline(&line, &len, fp) != -1) {
        //printf("tamano de linea: %zd\n", strlen(line));
        printf("string leido: %s", line);
        //copiamos el contenido leido del texto al msgq
        buflen = strlen(line)+1;
        strncpy(sbuf.mtext, line, buflen);
        if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
        {
            printf ("%d, %ld, %s, %d \n", msqid, sbuf.mtype, sbuf.mtext, (int)buflen);
            die("msgsnd");
        }
        else
            printf("Mensaje enviado.\n");
    }

    printf("\n\ntamano maximo de linea: %zd\n", len);

    fclose(fp);
    free(line);

    printf("Caught signal %d, coming out...\n", signum);
}
