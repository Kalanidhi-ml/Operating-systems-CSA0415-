#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex; // Controls access to read_count variable
sem_t wrt;   // Controls exclusive access to the shared database/resource
int read_count = 0;
int shared_data = 10; // The shared resource

void *reader(void *rno) {
    int id = *((int *)rno);

    // Entry Section for Reader
    sem_wait(&mutex);
    read_count++;
    if (read_count == 1) {
        sem_wait(&wrt); // First reader locks out writers
    }
    sem_post(&mutex);

    // Critical Section: Reading data
    printf("Reader %d: read shared data as %d\n", id, shared_data);
    sleep(1);

    // Exit Section for Reader
    sem_wait(&mutex);
    read_count--;
    if (read_count == 0) {
        sem_post(&wrt); // Last reader releases writer lock
    }
    sem_post(&mutex);

    pthread_exit(NULL);
}

void *writer(void *wno) {
    int id = *((int *)wno);

    // Entry Section for Writer
    sem_wait(&wrt);

    // Critical Section: Writing/Modifying data
    shared_data += 5;
    printf("Writer %d: modified shared data to %d\n", id, shared_data);
    sleep(1);

    // Exit Section for Writer
    sem_post(&wrt);

    pthread_exit(NULL);
}

int main() {
    pthread_t r[5], w[5];
    int ids[5] = {1, 2, 3, 4, 5};

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create Reader and Writer threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&r[i], NULL, reader, (void *)&ids[i]);
        pthread_create(&w[i], NULL, writer, (void *)&ids[i]);
    }

    // Join threads
    for (int i = 0; i < 3; i++) {
        pthread_join(r[i], NULL);
        pthread_join(w[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}