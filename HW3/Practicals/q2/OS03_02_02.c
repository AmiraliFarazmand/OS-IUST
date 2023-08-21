#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int counter = 0;
int mainCounter = 0;

sem_t mutex1;
sem_t mutex2;
sem_t mutex3;

void *Ehsan(void *args)
{
    printf("Ehsan arrived. Lets Wait for others!\n");
    sem_wait(&mutex1);
    counter++;
    sem_post(&mutex1);
    sem_wait(&mutex2);
    while (counter != 3)
        ;
    sem_post(&mutex2);
    printf("Ehsan left\n");
    sem_wait(&mutex3);
    mainCounter++;
    sem_post(&mutex3);
}

void *Alireza(void *args)
{
    printf("Alireza arrived. Lets Wait for others!\n");
    sem_wait(&mutex1);
    counter++;
    sem_post(&mutex1);
    sem_wait(&mutex2);
    while (counter != 3)
        ;
    sem_post(&mutex2);
    printf("Alireza left\n");
    sem_wait(&mutex3);
    mainCounter++;
    sem_post(&mutex3);
}

void *Armin(void *args)
{
    printf("Armin arrived. Lets Wait for others!\n");
    sem_wait(&mutex1);
    counter++;
    sem_post(&mutex1);
    sem_wait(&mutex2);
    while (counter != 3)
        ;
    sem_post(&mutex2);
    printf("Armin left\n");
    sem_wait(&mutex3);
    mainCounter++;
    sem_post(&mutex3);
}

int main()
{
    sem_init(&mutex1, 0, 1);
    sem_init(&mutex2, 0, 1);
    sem_init(&mutex3, 0, 1);
    pthread_t Friends[3];
    pthread_create(&Friends[0], NULL, Ehsan, NULL);
    pthread_create(&Friends[1], NULL, Alireza, NULL);
    pthread_create(&Friends[2], NULL, Armin, NULL);
    while (mainCounter != 3)
        ;
    sem_destroy(&mutex1);
    sem_destroy(&mutex2);
    sem_destroy(&mutex3);
}