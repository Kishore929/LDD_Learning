#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

#define MODULES_DIR "/lib/modules/"
#define DEP_FILE_FMT "/lib/modules/%s/modules.dep"

char kernel_version[256];

// Read kernel version for pathing
void get_kernel_version() {
    FILE *fp = popen("uname -r", "r");
    if (fp == NULL || fgets(kernel_version, sizeof(kernel_version), fp) == NULL) {
        perror("Failed to get kernel version");
        exit(EXIT_FAILURE);
    }
    kernel_version[strcspn(kernel_version, "\n")] = '\0'; // remove newline
    pclose(fp);
}

// Load a .ko file into the kernel
int load_module_file(const char *fullpath) {
    int fd = open(fullpath, O_RDONLY);
    if (fd < 0) {
        perror("open module");
        return -1;
    }

    struct stat st;
    fstat(fd, &st);
    void *image = malloc(st.st_size);
    if (!image) {
        perror("malloc");
        close(fd);
        return -1;
    }

    if (read(fd, image, st.st_size) != st.st_size) {
        perror("read");
        free(image);
        close(fd);
        return -1;
    }

    close(fd);
    int ret = syscall(SYS_init_module, image, st.st_size, "");
    free(image);
    if (ret != 0) {
        if (errno == EEXIST)
            printf("Module already loaded: %s\n", fullpath);
        else
            perror("init_module");
    } else {
        printf("Loaded module: %s\n", fullpath);
    }

    return ret;
}

// Recursively load dependencies
int load_module_with_deps(const char *module_name) {
    char dep_path[512];
    snprintf(dep_path, sizeof(dep_path), DEP_FILE_FMT, kernel_version);
    
    FILE *dep_file = fopen(dep_path, "r");
    if (!dep_file) {
        perror("fopen modules.dep");
        return -1;
    }

    char line[1024];
    char mod_path[512] = {0};

    while (fgets(line, sizeof(line), dep_file)) {
        if (strstr(line, module_name)) {
            char *colon = strchr(line, ':');
            if (!colon) continue;

            *colon = '\0';
            strncpy(mod_path, line, sizeof(mod_path));

            // Load dependencies first
            char *dep = colon + 2;  // skip ": "
            char *token = strtok(dep, " \n");
            while (token) {
                char full[512];
                snprintf(full, sizeof(full), "%s%s/%s", MODULES_DIR, kernel_version, token);
                load_module_file(full);
                token = strtok(NULL, " \n");
            }

            break;
        }
    }

    fclose(dep_file);

    if (strlen(mod_path) == 0) {
        fprintf(stderr, "Module %s not found in modules.dep\n", module_name);
        return -1;
    }

    // Load main module now
    char full_path[512];
    snprintf(full_path, sizeof(full_path), "%s%s/%s", MODULES_DIR, kernel_version, mod_path);
    return load_module_file(full_path);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <module_name.ko>\n", argv[0]);
        return EXIT_FAILURE;
    }

    get_kernel_version();
    return load_module_with_deps(argv[1]);
}
