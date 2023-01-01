#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <sys/wait.h>

/*
In this example we are going to demonstrate using pipe
as a mean for IPC. We are trying to compute for a number called x: ((x + c1) * c2 ) ^ c3 where
variable started with c are constants.
*/

#define IN_LEN 20
#define PIPE_NO 4
#define C1 10
#define C2 5
#define C3 2
#define FINISH -999

int sumUnit(int read_pipe, int write_pipe)
{
    while (1)
    {
        int input;
        read(read_pipe, &input, sizeof(int));
        printf("unit1:%d\n", input);
        if (input == FINISH)
        {
            int fin = FINISH;
            write(write_pipe, &fin, sizeof(int));
            return EXIT_SUCCESS;
        }
        input += C1;
        write(write_pipe, &input, sizeof(int));
    }
}

int multiplyUnit(int read_pipe, int write_pipe)
{
    while (1)
    {
        int input;
        read(read_pipe, &input, sizeof(int));
        printf("unit2: %d\n", input);
        if (input == FINISH)
        {
            int fin = FINISH;
            write(write_pipe, &fin, sizeof(int));
            return EXIT_SUCCESS;
        }
        input *= C2;
        write(write_pipe, &input, sizeof(int));
    }
}

int powerUnit(int read_pipe, int write_pipe)
{
    while (1)
    {
        int input;
        read(read_pipe, &input, sizeof(int));
        printf("unit3:%d\n", input);
        if (input == FINISH)
        {
            return EXIT_SUCCESS;
        }
        input *= input;
        write(write_pipe, &input, sizeof(int));
    }
}

int run(int pipes[PIPE_NO][2])
{
    int pid;
    pid = fork();
    if (pid > 0)
    {
        pid = fork();
        if (pid > 0)
        {
            sumUnit(pipes[0][0], pipes[1][1]);
            return EXIT_SUCCESS;
            // main ---- sum ---- multiply ----- power ---- main
        }
        else
        {
            multiplyUnit(pipes[1][0], pipes[2][1]);
            return EXIT_SUCCESS;
        }
    }
    else
    {
        powerUnit(pipes[2][0], pipes[3][1]);
        return EXIT_SUCCESS;
    }
}

int main()
{
    int userInputs[IN_LEN + 1];
    int outputs[IN_LEN];
    int pipes[PIPE_NO][2]; // [[i i] [i i] ... ]
    int pid;

    // initializing some numbers
    for (size_t i = 0; i < IN_LEN; i++)
        userInputs[i] = (i + 1) * 10;
    userInputs[IN_LEN] = FINISH;

    // Initialize pipes
    for (size_t i = 0; i < PIPE_NO; i++)
    {
        pipe(pipes[i]);
    }
    pid = fork();

    // Parent process
    if (pid == 0)
    {
        /*
        In this section I'm creating 3 new processes to run 3 available 
        units on them.
        Keep in mind that I'm terminating child processes!
        */
        run(pipes);
        exit(0);
    }
    else if (pid > 0)
    {
        pid = fork();
        if (pid > 0)
        {
            printf("Started reading\n");
            int output;
            for (size_t i = 0; i < IN_LEN; i++)
            {
                read(pipes[3][0], &outputs[i], sizeof(int));
                printf("((%d + %d)*%d)^%d= %d\n", userInputs[i], C1, C2, C3, outputs[i]);
            }
            printf("done\n");
            exit(0);
        }
        else if (pid == 0)
        {
            printf("Started writing\n");
            // Writing numbers
            for (size_t i = 0; i < IN_LEN + 1; i++)
            {
                write(pipes[0][1], &userInputs[i], sizeof(int));
                sleep(1);
            }
            exit(0);
        }
    }
    else
    {
        printf("Unable to create a new process\n");
        return EXIT_FAILURE;
    }
}
