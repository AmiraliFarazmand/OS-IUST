#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int fd[3][2];
    int pid[3];

    for ( int i = 0; i < 3; ++i ) {
        if ( pipe(fd[i]) == -1 ) {
            perror("pipe() failed");
            return EXIT_FAILURE;
        }

        if ( (pid[i] = fork()) == -1 ) {
            perror("fork() failed");
            return EXIT_FAILURE;
        }
        else if ( pid[i] == 0 ) {
            if ( close(fd[i][0]) == -1 ) {
                perror("close() failed");
                return EXIT_FAILURE;
            }

            char arr[100];
            sprintf(arr, "%d", i + 1);
            // sprintf(arr, "%d", msgs[i]);

            if ( write(fd[i][1], arr, 1) == -1 ) {
                perror("write() failed");
                return EXIT_FAILURE;
            }

            if ( close(fd[i][1]) == -1 ) {
                perror("close() failed");
                return EXIT_FAILURE;
            }

            return EXIT_SUCCESS;
        }
        else {
            if ( close(fd[i][1]) == -1 ) {
                perror("close() failed");
                return EXIT_FAILURE;
            }
        }
    }

    for ( int i = 0; i < 3; ++i ) {
        if ( waitpid(pid[i], NULL, 0) == -1 ) {
            perror("waitpid() failed");
            return EXIT_FAILURE;
        }

        char out[100] = {0};
        if ( read(fd[i][0], out, 99) == -1 ) {
            perror("read() failed");
            return EXIT_FAILURE;
        }

        printf("log of process:\t%s\n\n", out);

        if ( close(fd[i][0]) == -1 ) {
            perror("close() failed");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}