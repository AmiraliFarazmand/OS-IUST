// Links:
// https://stackoverflow.com/questions/35185503/how-to-write-to-a-file-using-open-and-printf
// https://stackoverflow.com/questions/28289157/c-multiprocessing-pipes

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/uio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <semaphore.h>

#define NUM_PROCESSES 8

int main(void)
{
    int fd[NUM_PROCESSES][2];
    pid_t pid[NUM_PROCESSES];

    for (int i = 0; i < NUM_PROCESSES; ++i)
    {
        if (pipe(fd[i]) == -1)
        {
            perror("pipe() failed");
            return EXIT_FAILURE;
        }

        if ((pid[i] = fork()) == -1)
        {
            perror("fork() failed");
            return EXIT_FAILURE;
        }
        else if (pid[i] == 0)
        {
            if (close(fd[i][0]) == -1)
            {
                perror("close() failed");
                return EXIT_FAILURE;
            }

            // EVERY PROCESS LOGS RIGHT HERE !!! sprintf arr redirected on pipe to  father process
            char arr[100];
            sprintf(arr, "%d", i + 1);

            if (write(fd[i][1], arr, 1) == -1)
            {
                perror("write() failed");
                return EXIT_FAILURE;
            }

            if (close(fd[i][1]) == -1)
            {
                perror("close() failed");
                return EXIT_FAILURE;
            }

            return EXIT_SUCCESS;
        }
        else
        {
            if (close(fd[i][1]) == -1)
            {
                perror("close() failed");
                return EXIT_FAILURE;
            }
        }
    }

    int fdLog;
    char *name = "a.log";
    fdLog = open(name, O_WRONLY | O_CREAT, 0644);
    if (fdLog == -1)
    {
        perror("open failed");
        exit(1);
    }

    if (dup2(fdLog, 1) == -1)
    {
        perror("dup2 failed");
        exit(1);
    }

    // file descriptor 1, i.e. stdout, now points to the file
    // "helloworld" which is open for writing
    // You can now use printf which writes specifically to stdout

    char *hi = "Hello World from file - logger activated";
    printf("%s\n", hi);

    for (int i = 0; i < NUM_PROCESSES; ++i)
    {
        if (waitpid(pid[i], NULL, 0) == -1)
        {
            perror("waitpid() failed");
            return EXIT_FAILURE;
        }

        char out[100] = {0};
        if (read(fd[i][0], out, 99) == -1)
        {
            perror("read() failed");
            return EXIT_FAILURE;
        }

        printf("log from proc%d: %s\n", i + 1, out);

        if (close(fd[i][0]) == -1)
        {
            perror("close() failed");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}