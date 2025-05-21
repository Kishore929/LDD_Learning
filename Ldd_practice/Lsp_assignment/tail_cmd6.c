// mytail.c
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#define DEFAULT_LINES 10
#define BUF_SIZE 1

int main(int argc, char *argv[]) {
    int fd, lines = DEFAULT_LINES;
    off_t pos;
    char ch;
    struct stat st;

    if (argc < 2) {
        write(2, "Usage: ./mytail <filename> [num_lines]\n", 39);
        return 1;
    }

    if (argc == 3)
        lines = atoi(argv[2]);

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    if (fstat(fd, &st) == -1) {
        perror("fstat");
        close(fd);
        return 1;
    }

    pos = st.st_size;
    int count = 0;

    while (pos > 0) {
        pos--;
        lseek(fd, pos, SEEK_SET);
        read(fd, &ch, 1);
        if (ch == '\n') {
            count++;
            if (count == lines + 1) break;
        }
    }

    while (read(fd, &ch, 1) == 1) {
        write(1, &ch, 1);
    }

    close(fd);
    return 0;
}
