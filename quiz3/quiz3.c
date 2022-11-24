/*
source code and tips for the problem:
    https://shivammitra.com/c/producer-consumer-problem-in-c/#
P.S. : didn't used srand(), So in tests you can see the difference in how threads work. 
*/
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
            printf("Consumer thread %d: I've got number %d from(buffer's index) %d; and it is EVEN!\n",*((int *)cno),item, out );
        else
            printf("Consumer thread %d: I've got number %d from(buffer's index) %d; and it is ODD!\n",*((int *)cno),item, out );
        out = (out+1)%n;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main()
{   


    printf("please enter n (size of buffer): ");
    scanf("%d" , &n);
    printf("please enter m (number of random numbres):");
    scanf("%d" , &m);
    printf("--------------------------------------------------------------------------------\n");


    pthread_t pro[5],con[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,n);
    sem_init(&full,0,0);
    
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