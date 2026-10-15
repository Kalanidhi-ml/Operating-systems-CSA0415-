#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd_src, fd_dest;
    ssize_t n_chars;
    char buffer[1024];

    fd_src = open("source.txt", O_RDONLY);
    if (fd_src < 0) {
        printf("Error opening source file.\n");
        return 1;
    }

    fd_dest = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dest < 0) {
        printf("Error opening/creating destination file.\n");
        close(fd_src);
        return 1;
    }

    while ((n_chars = read(fd_src, buffer, sizeof(buffer))) > 0) {
        write(fd_dest, buffer, n_chars);
    }

    close(fd_src);
    close(fd_dest);

    printf("File copied successfully.\n");
    return 0;
}