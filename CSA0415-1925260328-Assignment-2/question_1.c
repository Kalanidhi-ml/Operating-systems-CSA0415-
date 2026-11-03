/* Q1: Process Creation using fork() and inspecting via /proc */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    printf("Main Server PID: %d\n", getpid());
    
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        /* Child Process (Simulating Student Session) */
        printf("Student Session Child PID: %d, Parent PID: %d\n", getpid(), getppid());
        sleep(10); /* Keeps process alive long enough to check via ps or /proc */
        printf("Student Session Child exiting.\n");
        _exit(0);
    } else {
        /* Parent Process */
        printf("Parent created student session with PID: %d\n", pid);
        wait(NULL);
        printf("Child session terminated. Parent exiting.\n");
    }
    return 0;
}