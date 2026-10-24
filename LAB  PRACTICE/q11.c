#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* threadFunction(void* arg) {
    int thread_id = *((int*)arg);
    printf("Thread %d is running...\n", thread_id);
    sleep(1);
    printf("Thread %d has finished execution.\n", thread_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;

    printf("Main thread: Creating threads...\n");

    pthread_create(&thread1, NULL, threadFunction, &id1);
    pthread_create(&thread2, NULL, threadFunction, &id2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Main thread: All threads completed. Exiting.\n");

    return 0;
}