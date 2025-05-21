#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]) {
    int fd;
    char buf[BUF_SIZE];
    ssize_t nread;
    int lines = 0, words = 0, chars = 0;
    int in_word = 0;

    if (argc < 2) {
        write(2, "Usage: ./mywc <filename>\n", 26);
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    while ((nread = read(fd, buf, BUF_SIZE)) > 0) {
        chars += nread;
        for (int i = 0; i < nread; i++) {
            if (buf[i] == '\n') lines++;
            if (buf[i] == ' ' || buf[i] == '\n' || buf[i] == '\t') {
                in_word = 0;
            } else if (!in_word) {
                words++;
                in_word = 1;
            }
        }
    }

    if (nread < 0) {
        perror("read");
        close(fd);
        exit(1);
    }

    char output[256];
    int len = snprintf(output, sizeof(output), "Lines: %d  Words: %d  Chars: %d\n", lines, words, chars);
    write(1, output, len);

    close(fd);
    return 0;
}
