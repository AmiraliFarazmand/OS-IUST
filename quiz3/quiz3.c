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
#define BufferSize 6 // Size of the buffer              N

// int MaxItems;
// int BufferSize;

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
    for(int i = 0; i < MaxItems; i++) {
        srand(time(0));
        item = rand()%10000; // Produce an random item
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer thread %d: Generated number %d at(buffer's index) %d\n", *((int *)pno),buffer[in],in);
        in = (in+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}
void *consumer(void *cno)
{   
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        int result = item %2 ;
        printf("Consumer thread %d: I've got number %d from(buffer's index) %d; and is it odd:%d\n",*((int *)cno),item, out , result);
        out = (out+1)%BufferSize;
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

    // int n , m ;
    printf("please enter n (size of buffer):\t ");
    scanf("%d" , &n);
    printf("please enter m (number of random numbres):\t");
    scanf("%d" , &m);
    buffer =  (int *) malloc(sizeof(int) * n);
    int a[5] = {1,2,3,4,5}; //Just used for numbering the producer and consumer
    
    // for (int i = 0; i <n; i++){
    //     scanf("%d" ,&a[i]);
    // }
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