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

typedef struct
{
    int value;
    int counter;
    int process_unit;
} Prime_t;

bool check_prime(int a)
{
    int c;
    int lim = (int)sqrt(a);
    for (c = 2; c <= lim; c++)
    {
        if (a % c == 0)
            return false;
    }
    return true;
}

Prime_t *first_hundrend_prime_numbers()
{
    Prime_t *Prime_Numbers = (Prime_t *)malloc(100 * sizeof(Prime_t));
    int count = 0;
    for (int i = 2; count < 100; i++)
    {
        if (check_prime(i))
        {
            Prime_t temp;
            temp.value = temp.counter = i;
            temp.process_unit = i % NUM_PROCESSES;
            Prime_Numbers[count++] = temp;

        }
    }

    return Prime_Numbers;
}

int main(void)
{
    Prime_t *Prime_Numbers = first_hundrend_prime_numbers();
    int fd[2];
    pipe(fd);

    int pipes[2 * NUM_PROCESSES];
    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        pipe(&pipes[2 * i]);
    }

    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        if (fork() == 0)
        {
            Prime_t temp;
            while (read(pipes[i * 2], &temp, sizeof(Prime_t)) > 0)
            {
                if (temp.value == -1)
                    break;

                temp.value = temp.process_unit + temp.value;
                temp.counter--;
                temp.process_unit = (temp.process_unit + 1) % NUM_PROCESSES;
                write((temp.counter == 0) ? fd[1] : pipes[2 * temp.process_unit + 1], &temp, sizeof(Prime_t));
            }
            return 0;
        }
    }

    for (int i = 0; i < 100; i++)
    {
        write(pipes[2 * Prime_Numbers[i].process_unit + 1], &Prime_Numbers[i], sizeof(Prime_t));
    }

    for (int i = 0; i < 100; i++)
    {
        Prime_t temp;
        if (read(fd[0], &temp, sizeof(Prime_t)) > 0)
            printf("%d\t :%d th number\n",  temp.value ,i + 1);
    }

    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        Prime_t temp = {-1, 0, 0};
        write(pipes[i * 2 + 1], &temp, sizeof(Prime_t));
    }
    return 0;
}