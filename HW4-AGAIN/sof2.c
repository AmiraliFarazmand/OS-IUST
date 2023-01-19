/*
Useful links:
    https://www.geeksforgeeks.org/pipe-system-call/
    https://stackoverflow.com/questions/28289157/c-multiprocessing-pipes

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define PROC_COUNT 7
int main(void)
{
    int fd[PROC_COUNT][2];
    int pid[PROC_COUNT];

    for ( int i = 0; i < PROC_COUNT; ++i ) {
        pipe(fd[i]);

        pid[i] = fork();

        if ( pid[i] == 0 ) {
            close(fd[i][0]);

            char arr[100];
            sprintf(arr, "%d", i + 1);
            write(fd[i][1], arr, 1) ;

            close(fd[i][1]) ;

            return 0;
        }
        else {
            close(fd[i][1]) ;
            }
    }

    for ( int i = 0; i < PROC_COUNT; ++i ) {
        waitpid(pid[i], NULL, 0);

        char out[100] = {0};
        read(fd[i][0], out, 99);

        printf("log of process:\t%s\n\n", out);

        close(fd[i][0]);
    }

    return 0;
}