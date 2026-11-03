/* Q3: POSIX Threads for Traffic Camera Frame Processing */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_CAMERAS 64

void *process_camera(void *arg) {
    int camera_id = *(int *)arg;
    // Simulate processing frame data
    usleep(10000); 
    // printf("Camera %d processed successfully.\n", camera_id);
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_CAMERAS];
    int cam_ids[NUM_CAMERAS];

    for (int i = 0; i < NUM_CAMERAS; i++) {
        cam_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, process_camera, &cam_ids[i]);
    }

    for (int i = 0; i < NUM_CAMERAS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All %d traffic cameras processed successfully using POSIX threads.\n", NUM_CAMERAS);
    return 0;
}