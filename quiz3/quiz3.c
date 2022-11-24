/*
source code and tips for the problem:
    https://shivammitra.com/c/producer-consumer-problem-in-c/#
*/
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
/*
This program provides a possible solution for producer-consumer problem using mutex and semaphore.
I have used 5 producers and 5 consumers to demonstrate the solution. You can always play with these values.
*/

#define MaxItems 5 // Maximum items a producer can produce or a consumer can consume            M
#define BufferSize 7 // Size of the buffer              N


int n,m ;

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int* buffer;
pthread_mutex_t mutex;

void *producer(void *pno)
{   
    int item;
    for(int i = 0; i < m; i++) {
        // srand(time(0));
        item = rand()%1000; // Produce an random item
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer thread %d: Generated number %d at(buffer's index) %d\n", *((int *)pno),buffer[in],in);
        in = (in+1)%n;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *cno)
{   
    for(int i = 0; i < m; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        int result = item %2 ;
        if (result==0)
            printf("Consumer thread %d: I've got number %d from(buffer's index) %d; and is it EVEN!\n",*((int *)cno),item, out );
        else
            printf("Consumer thread %d: I've got number %d from(buffer's index) %d; and is it ODD!\n",*((int *)cno),item, out );
        out = (out+1)%n;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main()
{   

    pthread_t pro[5],con[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);

    printf("please enter n (size of buffer): ");
    scanf("%d" , &n);
    printf("please enter m (number of random numbres):");
    scanf("%d" , &m);
    buffer =  (int *) malloc(sizeof(int) * n);
    int a[3] = {0,1,2}; //Just used for numbering the producer and consumer (for naming threads )

    for(int i = 0; i < 3; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for(int i = 0; i < 3; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    for(int i = 0; i < 3; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < 3; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
    
}