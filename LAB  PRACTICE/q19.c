#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define ITERATIONS 100000

// Shared resource variable
long long shared_counter = 0;

// Declare a mutex lock
pthread_mutex_t lock;

// Thread function that increments the shared counter
void *increment_counter(void *arg) {
    int thread_id = *((int *)arg);

    for (int i = 0; i < ITERATIONS; i++) {
        // Enter Critical Section: Lock the mutex
        pthread_mutex_lock(&lock);

        // Critical Section
        shared_counter++;

        // Exit Critical Section: Unlock the mutex
        pthread_mutex_unlock(&lock);
    }

    printf("Thread %d finished execution.\n", thread_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize the mutex lock
    if (pthread_mutex_init(&lock, NULL) != 0) {
        perror("Mutex initialization failed");
        return 1;
    }

    // Create multiple threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, increment_counter, (void *)&thread_ids[i]) != 0) {
            perror("Thread creation failed");
            return 1;
        }
    }

    // Wait for all threads to complete execution
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Output results
    long long expected_value = (long long)NUM_THREADS * ITERATIONS;
    printf("\n--- Synchronization Results ---\n");
    printf("Final Shared Counter Value: %lld\n", shared_counter);
    printf("Expected Counter Value:     %lld\n", expected_value);

    if (shared_counter == expected_value) {
        printf("SUCCESS: Mutex successfully prevented race conditions!\n");
    } else {
        printf("ERROR: Race condition detected (value mismatch).\n");
    }

    // Destroy the mutex lock
    pthread_mutex_destroy(&lock);

    return 0;
}