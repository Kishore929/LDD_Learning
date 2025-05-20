#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>   // for basename()
#include <sys/stat.h>
#include <limits.h>  // <-- THIS is required for PATH_MAX


#define BUF_SIZE 4096

int main(int argc, char *argv[]) {
    int src_fd, dest_fd;
    ssize_t nread;
    char buffer[BUF_SIZE];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_directory>\n", argv[0]);
        return 1;
    }

    // Get source filename
    char *filename = basename(argv[1]);

    // Create full destination path: dest_dir + "/" + filename
    char dest_path[PATH_MAX];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", argv[2], filename);

    // Open source file
    src_fd = open(argv[1], O_RDONLY);
    if (src_fd < 0) {
        perror("Error opening source file");
        return 1;
    }

    // Open destination file
    dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error creating destination file");
        close(src_fd);
        return 1;
    }

    // Copy contents
    while ((nread = read(src_fd, buffer, BUF_SIZE)) > 0) {
        if (write(dest_fd, buffer, nread) != nread) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            return 1;
        }
    }

    if (nread < 0) {
        perror("Error reading from source file");
    }

    close(src_fd);
    close(dest_fd);

    printf("✅ File copied to: %s\n", dest_path);
    return 0;
}

