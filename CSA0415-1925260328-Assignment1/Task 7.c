#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    printf("shell: running job 1\n");
    fflush(stdout); /* empty the buffer before fork() */
    
    // TODO 1: Create a child with fork(). In the child, replace the program with
    // execlp("expr", "expr", "6", "*", "7", (char *)NULL) and exit(127) if exec fails.
    // In the parent, wait for the child with waitpid() and print "job 1 exit status N" using WEXITSTATUS.
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        execlp("expr", "expr", "6", "*", "7", (char *)NULL);
        _exit(127);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("job 1 exit status %d\n", WEXITSTATUS(status));
        }
    }

    printf("shell: running job 2\n");
    fflush(stdout);
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) _exit(3); /* a child that fails with code 3 */
    int status2;
    waitpid(pid, &status2, 0);
    printf("job 2 exit status %d\n", WEXITSTATUS(status2));
    return 0;
}