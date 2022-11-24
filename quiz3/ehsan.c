#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// defining M N

int N;
int M;
int producingIndex = 0;
int consumingIndex = 0;
sem_t FullSemaphore;
sem_t EmptySemaphore;
sem_t mutex;
int *buffer;

// producer function

void *producer(void *producerCounter)
{
    int m = M;
    while (m > 0)
    {
        int randomNumber = rand();
        sem_wait(&EmptySemaphore);
        sem_wait(&mutex);
        int x = randomNumber % 100;
        buffer[producingIndex] = x;
        producingIndex = (producingIndex + 1) % N;
        printf("Producer Thread %d: Generated number %d\n", *((int *)producerCounter), x);
        sem_post(&mutex);
        sem_post(&FullSemaphore);
        m--;
    }
}

// consumer function

void *consumer(void *consumerCounter)
{
    int m = M;
    while (m > 0)
    {
        sem_wait(&FullSemaphore);
        sem_wait(&mutex);
        int consumedNumber = buffer[consumingIndex];
        consumingIndex = (consumingIndex + 1) % N;
        char *evenOrOdd = "odd";
        if (consumedNumber % 2 == 0)
        {
            evenOrOdd = "even";
        }
        printf("Consumer Thread %d: I got number %d, and its %s\n", *((int *)consumerCounter), consumedNumber, evenOrOdd);
        sem_post(&mutex);
        sem_post(&EmptySemaphore);
        m--;
    }
}

int main()
{
    // gettin m n
    printf("N:\n");
    scanf("%d", &N);
    printf("M:\n");
    scanf("%d", &M);
    buffer = (int *)malloc(sizeof(int) * N);

    // creating threads and semaphores
    pthread_t ProducerthreadIDs[3];
    pthread_t ConsumerthreadIDs[3];

    sem_init(&mutex, 0, 1);
    sem_init(&FullSemaphore, 0, 0);
    sem_init(&EmptySemaphore, 0, N);

    int threadCounter[3] = {1, 2, 3};

    pthread_create(&ProducerthreadIDs[0], NULL, producer, (void *)&threadCounter[0]);
    pthread_create(&ProducerthreadIDs[1], NULL, producer, (void *)&threadCounter[1]);
    pthread_create(&ProducerthreadIDs[2], NULL, producer, (void *)&threadCounter[2]);
    pthread_create(&ConsumerthreadIDs[0], NULL, consumer, (void *)&threadCounter[0]);
    pthread_create(&ConsumerthreadIDs[1], NULL, consumer, (void *)&threadCounter[1]);
    pthread_create(&ConsumerthreadIDs[2], NULL, consumer, (void *)&threadCounter[2]);

    pthread_join(ProducerthreadIDs[0], NULL);
    pthread_join(ProducerthreadIDs[1], NULL);
    pthread_join(ProducerthreadIDs[2], NULL);
    pthread_join(ConsumerthreadIDs[0], NULL);
    pthread_join(ConsumerthreadIDs[1], NULL);
    pthread_join(ConsumerthreadIDs[2], NULL);

    sem_destroy(&mutex);
    sem_destroy(&FullSemaphore);
    sem_destroy(&EmptySemaphore);

    return 0;
}