/*****************************************************************************
 Excerpt from "Linux Programmer's Guide - Chapter 6"
 (C)opyright 1994-1995, Scott Burkett
 ***************************************************************************** 
 MODULE: pipe.c
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>


int c;


int main(void)
{
        int     fd[2], nbytes;
        pid_t   childpid;
        char    string[] = "Hello, world!\n";
        char    readbuffer[80];
        int c;
        // funcion pipe
        pipe(fd);

        //se hace fork al padre
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        printf("Main program:"); 
        c=getchar();
        printf("M %c\n",c);
        // si es el hijo
        if(childpid == 0)
        {
                int c;
                printf("Child program:"); 
                c=getchar();
                printf("C %c\n",c);
                /* Child process closes up input side of pipe */
                close(fd[0]);

                /* Send "string" through the output side of pipe */
                // se escribe en archivo con la funcion write
                // (file descriptor, buffer, size)
                write(fd[1], string, (strlen(string)+1));
                exit(0);
        }
        else
        {
                int c;
                printf("Parent program:"); 
                c=getchar();
                printf("P %c\n",c);
                /* Parent process closes up output side of pipe */
                close(fd[1]);

                /* Read in a string from the pipe */
                // lee la informacion del file descriptor
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("Received string: %s", readbuffer);
        }

        return(0);
}
