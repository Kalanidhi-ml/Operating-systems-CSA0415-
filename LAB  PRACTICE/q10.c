#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    const char *queue_name = "/test_queue";
    mqd_t mq;
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 1024;
    attr.mq_curmsgs = 0;

    mq_unlink(queue_name);

    mq = mq_open(queue_name, O_CREAT | O_RDWR, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        const char *msg = "Hello from Child Process via Message Queue!";
        if (mq_send(mq, msg, strlen(msg) + 1, 0) == -1) {
            perror("mq_send failed");
            exit(1);
        }
        exit(0);
    } else {
        wait(NULL);
        char buffer[1024];
        if (mq_receive(mq, buffer, 1024, NULL) == -1) {
            perror("mq_receive failed");
            exit(1);
        }
        printf("Parent process received from message queue:\n%s\n", buffer);

        mq_close(mq);
        mq_unlink(queue_name);
    }

    return 0;
}
