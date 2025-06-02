/*****************************  KERNEL MASTERS ********************************
 * 
 * Name : km
 * Date : 31-05-2025
 * File_Name : 
 * Sample_Input :
 * Sample_Output :
 *
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define NUM_ITERATIONS 100000

int counter = 0;
pthread_mutex_t lock;

void *increment(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&lock);   // Enter critical section
        counter++;
        pthread_mutex_unlock(&lock); // Exit critical section
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize the mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        perror("Mutex init failed");
        return 1;
    }

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, increment, NULL) != 0) {
            perror("Thread creation failed");
            return 1;
        }
    }

    // Wait for threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    printf("Final counter value: %d (expected: %d)\n", counter, NUM_THREADS * NUM_ITERATIONS);
    return 0;
}

