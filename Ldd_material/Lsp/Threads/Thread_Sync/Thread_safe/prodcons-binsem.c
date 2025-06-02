#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

void *producer(void *arg);
void *consumer(void *arg);
//int counter = 0;
char buffer[5];
sem_t prod,cons;// two binary sema

int main() {
    int res;
    pthread_t a_thread,b_thread;
    void *thread_result;
    
    sem_init(&prod,0,1);
    sem_init(&cons,0,0);

    res = pthread_create(&a_thread, NULL, producer, NULL);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&b_thread, NULL, consumer, NULL);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Wait for pthread_join\n");
    res = pthread_join(a_thread, &thread_result);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_join(b_thread, &thread_result);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined\n");
    exit(EXIT_SUCCESS);
}

void *producer(void *arg) {
    int i = 0; 
    char ch='A';
    while(1)
	{
	//	printf ("producer: counter:%d\n",counter); 
		sem_wait(&prod);
		//while(counter == 5);
		for(i=0;i<5;i++)
		{
			buffer[i]=ch;
			ch++;
		}
		ch='A';
		printf("p:%s\n",buffer);
		sem_post(&cons);
		//counter++;
	}
	
   pthread_exit("exit");	
}
void *consumer(void *arg) {
    int i = 0;
    char data[5];
    while(1)
	{
		sem_wait(&cons);
		//while(counter == 0);
		for(i=0;i<5;i++){
			data[i] = buffer[i];
		}
		printf ("\t:c:%s\n",data); 
		//counter--;
		sem_post(&prod);
	}
   pthread_exit("exit");	
}
