#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty; // Counts empty buffer slots
sem_t full;  // Counts filled buffer slots
pthread_mutex_t mutex; // Controls access to critical section

void *producer(void *pNo) {
    int item;
    for (int i = 0; i < 5; i++) {
        item = rand() % 100; // Produce an item

        sem_wait(&empty); // Decrement empty slots (wait if buffer is full)
        pthread_mutex_lock(&mutex); // Enter critical section

        // Critical Section: Add item to buffer
        buffer[in] = item;
        printf("Producer %d: Inserted item %d at index %d\n", *((int *)pNo), item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full); // Increment full slots (signal consumer)

        sleep(1); // Sleep to simulate production time
    }
    pthread_exit(NULL);
}

void *consumer(void *cNo) {
    int item;
    for (int i = 0; i < 5; i++) {
        sem_wait(&full); // Decrement full slots (wait if buffer is empty)
        pthread_mutex_lock(&mutex); // Enter critical section

        // Critical Section: Remove item from buffer
        item = buffer[out];
        printf("Consumer %d: Removed item %d from index %d\n", *((int *)cNo), item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty); // Increment empty slots (signal producer)

        sleep(2); // Sleep to simulate consumption time
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod[2], cons[2];
    int p_id[2] = {1, 2};
    int c_id[2] = {1, 2};

    // Initialize mutex and semaphores
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE); // Initially, all slots are empty
    sem_init(&full, 0, 0);            // Initially, no slots are full

    // Create Producer and Consumer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&prod[i], NULL, producer, (void *)&p_id[i]);
        pthread_create(&cons[i], NULL, consumer, (void *)&c_id[i]);
    }

    // Join threads
    for (int i = 0; i < 2; i++) {
        pthread_join(prod[i], NULL);
        pthread_join(cons[i], NULL);
    }

    // Destroy semaphores and mutex
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}