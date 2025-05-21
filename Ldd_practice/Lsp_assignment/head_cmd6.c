// myhead.c
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int fd;
    int lines = 10;
    char ch;
    ssize_t n;

    if (argc < 2) {
        write(2, "Usage: ./myhead <file> [num_lines]\n", 36);
        exit(1);
    }

    if (argc == 3) {
        lines = atoi(argv[2]);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    while ((n = read(fd, &ch, 1)) > 0 && lines > 0) {
        write(1, &ch, 1);
        if (ch == '\n') {
            lines--;
        }
    }

    close(fd);
    return 0;
}
