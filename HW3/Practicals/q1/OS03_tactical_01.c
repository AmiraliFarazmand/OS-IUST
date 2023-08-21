#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

pthread_mutex_t lock;
double answear = 0;
long pointer = 0;

typedef struct
{
    long NumberOfCalculationsForEachThread;
    long remainingCalculations;
} NumberOfCalculations;

void *CalculatorFunc(void *args)
{
    pthread_mutex_lock(&lock);
    NumberOfCalculations *NOC = args;
    for (int i = 0; i < (NOC->NumberOfCalculationsForEachThread + NOC->remainingCalculations); i++)
    {
        double answearAdding = (double)(pow(-1, pointer)) / (2 * pointer + 1);
        answear += answearAdding;
        pointer++;
    }
    pthread_mutex_unlock(&lock);
}

int main()
{

    long n;
    printf("Give me n:\n");
    scanf("%ld", &n);
    long threadNumbers;
    printf("Give me the number of threads to work with:\n");
    scanf("%ld", &threadNumbers);
    pthread_t threads[threadNumbers];
    for (int i = 0; i < threadNumbers; i++)
    {
        NumberOfCalculations *args = malloc(sizeof *args);
        args->NumberOfCalculationsForEachThread = n / threadNumbers;
        args->remainingCalculations = 0;
        if (i == (threadNumbers - 1))
        {
            args->remainingCalculations = n % threadNumbers;
        }
        pthread_create(&threads[i], NULL, &CalculatorFunc, args);
    }
    for (int i = 0; i < threadNumbers; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Final answear:%f\n", answear);

    return 0;
}
