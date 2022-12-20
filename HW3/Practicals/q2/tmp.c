/*
A program that implemented Barrier using semaphore and conditional variables
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
sem_t mutex;   // to handle global variable <n>
sem_t barrier; // to make threads stop until counter reaches n

int n = 4; // number of threads that we create in main
int counter = 0;

void *func(void *s)
{
	printf("func with attribute:%s called. Now it's time to wait for others!\n", (char *)s);
	sem_wait(&mutex);
	counter = counter + 1;
	sem_post(&mutex);

	if (counter == n)
	{
		sem_post(&barrier);
	}
	sem_wait(&barrier);
	sem_post(&barrier);

	printf("func with attribute:%s Ended!\n", (char *)s);
}

int main()
{
	pthread_t t0, t1, t2, t3;
	sem_init(&mutex, 0, 1);
	sem_init(&barrier, 0, 0);

	pthread_create(&t0, 0, func, "jafar");
	pthread_create(&t1, 0, func, "asqar");
	pthread_create(&t2, 0, func, "akbar");
	pthread_create(&t3, 0, func, "qolli");

	pthread_join(t0, 0);
	pthread_join(t1, 0);
	pthread_join(t2, 0);
	pthread_join(t3, 0);
	return 0;
}