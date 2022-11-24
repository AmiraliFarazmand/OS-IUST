// C program to demonstrate working of Semaphores
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
  
sem_t mutex;
// ------------------------------------------------------------------------------------------------
void* producer(void* arg){

    //wait
    sem_wait(&mutex);
    printf("\nEntered..\n");
  
    //critical section
    sleep(4);
      
    //signal
    printf("\nJust Exiting...\n");
    sem_post(&mutex);
}
// ------------------------------------------------------------------------------------------------
void* consumer(void* arg){

    //wait
    sem_wait(&mutex);
    printf("\nEntered..\n");
  
    //critical section
    sleep(4);
      
    //signal
    printf("\nJust Exiting...\n");
    sem_post(&mutex);
}
// =================================================================================================
int main()
{
    sem_init(&mutex, 0, 2);
    pthread_t t1,t2 ,t3;
    int n , m ;
    printf("please enter n (size of buffer):\t ");
    scanf("%d" , &n);
    printf("please enter m (number of random numbres):\t");
    scanf("%d" , &m);
    pthread_create(&t1,NULL,producer,NULL);
    sleep(2);
    pthread_create(&t2,NULL,producer,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&mutex);
    return 0;
}
