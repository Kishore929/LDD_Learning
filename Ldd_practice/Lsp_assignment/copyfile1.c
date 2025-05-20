
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 4096

int fd, fd2;
ssize_t nread, nwrite;
char buffer[BUF_SIZE];


int main(int argc, char *argv[])
{

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    fd2 = open(argv[2], O_RDWR);
    if (fd2 < 0) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }
    // nread = read(fd, buffer, BUF_SIZE);

    // nwrite = write(fd2, &buffer, nread);

     while ((nread = read(fd, buffer, BUF_SIZE)) > 0) {
        nwrite = write(fd2, buffer, nread);
        if (nwrite != nread) {
            perror("Error writing to destination");
            close(fd);
            close(fd2);
            exit(EXIT_FAILURE);
        }
    }

    close(fd);
    close(fd2);

    exit(0);

}