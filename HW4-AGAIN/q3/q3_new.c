/*
Useful links:
    https://www.geeksforgeeks.org/pipe-system-call/
    https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/
    https://stackoverflow.com/questions/28289157/c-multiprocessing-pipes

*/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define PROC_COUNT 5
int main(char **argv)
{
    int fd[PROC_COUNT][2];
    int pid[PROC_COUNT];

    for ( int i = 0; i < PROC_COUNT; ++i ) {
        pipe(fd[i]);

        pid[i] = fork();

        if ( pid[i] == 0 ) {
            close(fd[i][0]);

            char in_a[100];
            sprintf(in_a, "%d", i + 1);
            write(fd[i][1], in_a, 1) ;

            close(fd[i][1]) ;

            return 0;
        }
        else { // pid[i] == 0
            close(fd[i][1]) ;
            }
    }

    for ( int i = 0; i < PROC_COUNT; ++i ) {
        waitpid(pid[i], NULL, 0);

        char output[100] = {0};
        read(fd[i][0], output, 99);

        printf("log No:\t%s\n\n", output);

        close(fd[i][0]);
    }
    return 0;
}