#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define SIZE 5

char buffer[SIZE];
int count = 0;
int in = 0, out = 0;

pthread_t producer_thread, consumer_thread;

// Signal handler for producer (SIGUSR1)
void prod_sig(int sig) {
    // Produce until buffer is full
    while (count < SIZE) {
        buffer[in] = 'A' + in;
        in = (in + 1) % SIZE;
        count++;
    }

    printf("Producer produced: %.*s\n", SIZE, buffer);

    // Signal consumer
    pthread_kill(consumer_thread, SIGUSR2);

    printf("Producer exiting.\n");
    pthread_exit(NULL);
    
}

// Producer thread
void *producer(void *arg) {
    // Register signal handler
    signal(SIGUSR1, prod_sig);

    while (1) {
        pause(); // Wait for consumer signal
    }

    // return NULL;
}

// Signal handler for consumer (SIGUSR2)
void cons_sig(int sig) {
    // Consume until buffer is empty
    char data[SIZE];
    int i = 0;

    while (count > 0) {
        data[i++] = buffer[out];
        out = (out + 1) % SIZE;
        count--;
    }

    printf("\tConsumer consumed: %.*s\n", SIZE, data);

    // Signal producer
    // pthread_kill(producer_thread, SIGUSR1);
    printf("Consumer exiting.\n");
    pthread_exit(NULL);
}

// Consumer thread
void *consumer(void *arg) {
    // Register signal handler
    signal(SIGUSR2, cons_sig);

    // Initially start the cycle by signaling producer
    sleep(1); // Allow threads to set up signal handlers
    pthread_kill(producer_thread, SIGUSR1);

    while (1) {
        pause(); // Wait for producer signal
    }

    // pthread_exit("Thank you for the CPU time");
    // pthread_exit(NULL);
    // return NULL;
}

int main() {
    // Create threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads (they actually loop forever)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    printf("Main: Both threads finished. Exiting.\n");
    return 0;
}
