/*
A program that implemented Barrier using Mutex and conditional variable . Couldn't figure out how to implement it without using those variables.
*/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t mutex;    // to handle global variable <n> 
pthread_mutex_t barrier;  // to make threads stop until counter reaches n 

int n=4;    //number of threads that we create in main 
int counter=0;  

void *func(void *s)
{
	printf("func with attribute:%s called. Now it's time to wait for others!\n", (char *)s);

    pthread_mutex_lock(&mutex) ;
	counter = counter + 1;
    pthread_mutex_unlock(&mutex) ;

    pthread_mutex_lock(&barrier) ;
    while (counter!=n);
    pthread_mutex_unlock(&barrier);

	printf("func with attribute:%s Ended!\n", (char *)s);
}

int main()
{
	pthread_t t0, t1, t2, t3;
	
    pthread_mutex_init(&barrier, NULL) ;
    pthread_mutex_init(&mutex ,NULL);
    
    pthread_create(&t0, 0, func, "jafar");
	pthread_create(&t1, 0, func, "asqar");
	pthread_create(&t2, 0, func, "akbar");
	pthread_create(&t3, 0, func, "qolli");
    
	
    pthread_join(t0, 0);
	pthread_join(t1, 0);
	pthread_join(t2, 0);
	pthread_join(t3, 0);
    
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&barrier);
    return 0;
}