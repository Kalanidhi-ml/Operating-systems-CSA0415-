#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t forks[N];
pthread_t philosophers[N];
int phil_ids[N];

void* philosopher(void* num) {
    int id = *((int*)num);

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        if (id % 2 == 0) {
            pthread_mutex_lock(&forks[id]);
            pthread_mutex_lock(&forks[(id + 1) % N]);
        } else {
            pthread_mutex_lock(&forks[(id + 1) % N]);
            pthread_mutex_lock(&forks[id]);
        }

        printf("Philosopher %d is eating.\n", id);
        sleep(1);

        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id + 1) % N]);

        printf("Philosopher %d finished eating and is thinking.\n", id);
        sleep(1);
    }
}

int main() {
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        phil_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &phil_ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}