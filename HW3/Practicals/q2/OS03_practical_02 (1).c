#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

int counter = 0;
int mainCounter = 0;
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

void *Ehsan(void *args)
{
    printf("Ehsan arrived. Lets Wait for others!\n");
    pthread_mutex_lock(&mutex1);
    counter++;
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_lock(&mutex2);
    while (counter != 3)
        ;
    pthread_mutex_unlock(&mutex2);
    printf("Ehsan left\n");
    mainCounter++;
}

void *Alireza(void *args)
{
    printf("Alireza arrived. Lets Wait for others!\n");
    pthread_mutex_lock(&mutex1);
    counter++;
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_lock(&mutex2);
    while (counter != 3)
        ;
    pthread_mutex_unlock(&mutex2);
    printf("Alireza left\n");
    mainCounter++;
}

void *Armin(void *args)
{
    printf("Armin arrived. Lets Wait for others!\n");
    pthread_mutex_lock(&mutex1);
    counter++;
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_lock(&mutex2);
    while (counter != 3)
        ;
    pthread_mutex_unlock(&mutex2);
    printf("Armin left\n");
    mainCounter++;
}

int main()
{
    pthread_t Friends[3];
    pthread_create(&Friends[0], NULL, Ehsan, NULL);
    pthread_create(&Friends[1], NULL, Alireza, NULL);
    pthread_create(&Friends[2], NULL, Armin, NULL);
    while (mainCounter != 3)
        ;
}