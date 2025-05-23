#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <utime.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int fd;

    // Try opening the file
    fd = open(filename, O_WRONLY | O_CREAT, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    close(fd);

    // Update access and modification times to current time
    if (utime(filename, NULL) != 0) {
        perror("utime");
        return 1;
    }

    return 0;
}
