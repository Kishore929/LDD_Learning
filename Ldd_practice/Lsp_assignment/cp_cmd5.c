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

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#define BUF_SIZE 4096

void copy_file(const char *src, const char *dest) {
    int fd_src = open(src, O_RDONLY);
    if (fd_src < 0) {
        perror("open src");
        return;
    }

    int fd_dest = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dest < 0) {
        perror("open dest");
        close(fd_src);
        return;
    }

    char buf[BUF_SIZE];
    ssize_t nread;
    while ((nread = read(fd_src, buf, BUF_SIZE)) > 0) {
        if (write(fd_dest, buf, nread) != nread) {
            perror("write");
            break;
        }
    }

    close(fd_src);
    close(fd_dest);
}

void copy_dir(const char *src, const char *dest) {
    DIR *dir = opendir(src);
    if (!dir) {
        perror("opendir");
        return;
    }

    mkdir(dest, 0755);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char path_src[1024], path_dest[1024];
        snprintf(path_src, sizeof(path_src), "%s/%s", src, entry->d_name);
        snprintf(path_dest, sizeof(path_dest), "%s/%s", dest, entry->d_name);

        struct stat st;
        stat(path_src, &st);

        if (S_ISDIR(st.st_mode)) {
            // Recursively copy subdirectory
            copy_dir(path_src, path_dest);
        } else if (S_ISREG(st.st_mode)) {
            // Copy file
            copy_file(path_src, path_dest);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 4 || strcmp(argv[1], "-r") != 0) {
        fprintf(stderr, "Usage: %s -r <source_dir> <destination_dir>\n", argv[0]);
        return 1;
    }

    struct stat st;
    stat(argv[2], &st);
    if (S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Destination already exists!\n");
        return 1;
    }

    copy_dir(argv[2], argv[3]);
    printf("Directory copied successfully.\n");

    return 0;
}

*/