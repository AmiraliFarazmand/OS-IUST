// C program to demonstrate working of Semaphores
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
  
sem_t mutex1;
sem_t mutex2;
  
void* thread1(void* arg)
{
    //wait
    sem_wait(&mutex1);
    printf("\nEntered thread1 and got mutex 1 so i am going to sleep for 2 second and get mutex 2..\n");
    sleep(2);
    sem_wait(&mutex2);
    //critical section
    sleep(4);
      
    //signal
    printf("\nJust Exiting...\n");
    sem_post(&mutex1);
    sem_post(&mutex2);
}
  
void* thread2(void* arg)
{
    //wait
    sem_wait(&mutex2);
    printf("\nEntered thread2 and got mutex 2 so i am going to sleep for 2 second and get mutex 1..\n");
    sleep(2);
    sem_wait(&mutex1);
  
    //critical section
    sleep(4);
      
    //signal
    printf("\nJust Exiting...\n");
    sem_post(&mutex2);
    sem_post(&mutex1);
}

int main()
{
    sem_init(&mutex1, 0, 1);
    sem_init(&mutex2, 0, 1);

    pthread_t t1,t2;
    pthread_create(&t1,NULL,thread1,NULL);
    pthread_create(&t2,NULL,thread2,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&mutex1);
    sem_destroy(&mutex2);
    return 0;
}
