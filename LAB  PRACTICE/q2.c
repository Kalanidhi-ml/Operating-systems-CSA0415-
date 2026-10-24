#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    int fd_src = open(argv[1], O_RDONLY);
    if (fd_src < 0) {
        perror("Error opening source file");
        return 1;
    }

    int fd_dest = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd_dest < 0) {
        perror("Error opening destination file");
        close(fd_src);
        return 1;
    }

    char buffer[1024];
    ssize_t bytes_read, bytes_written;

    while ((bytes_read = read(fd_src, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(fd_dest, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(fd_src);
            close(fd_dest);
            return 1;
        }
    }

    if (bytes_read < 0) {
        perror("Error reading source file");
    }

    close(fd_src);
    close(fd_dest);

    printf("File copied successfully.\n");

    return 0;
}