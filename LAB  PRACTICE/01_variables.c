#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    } 
    else if (pid == 0) {
        printf("--- Inside Child Process ---\n");
        printf("Child Process ID (PID): %d\n", (int)getpid());
        printf("Parent Process ID (PPID): %d\n", (int)getppid());
    } 
    else {
        printf("--- Inside Parent Process ---\n");
        printf("Parent Process ID (PID): %d\n", (int)getpid());
        printf("Parent's Parent ID (PPID): %d\n", (int)getppid());
        printf("Child Process ID created: %d\n", (int)pid);
    }

    return 0;
}