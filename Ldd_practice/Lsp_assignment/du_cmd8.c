
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define KB 1024
#define MB (1024 * KB)
#define GB (1024 * MB)

long get_dir_size(const char *path) {
    struct stat st;
    DIR *dir;
    struct dirent *entry;
    char fullpath[4096];
    long total_size = 0;

    if (lstat(path, &st) == -1) {
        perror("lstat");
        return 0;
    }

    // If it's a file, return its size
    if (!S_ISDIR(st.st_mode)) {
        return st.st_size;
    }

    dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return 0;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        total_size += get_dir_size(fullpath);
    }

    closedir(dir);
    return total_size;
}

void print_human_readable(long size) {
    if (size >= GB)
        printf("%.2f GB\n", (float)size / GB);
    else if (size >= MB)
        printf("%.2f MB\n", (float)size / MB);
    else if (size >= KB)
        printf("%.2f KB\n", (float)size / KB);
    else
        printf("%ld B\n", size);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    long total_size = get_dir_size(argv[1]);
    printf("Total size of %s: ", argv[1]);
    print_human_readable(total_size);

    return 0;
}
