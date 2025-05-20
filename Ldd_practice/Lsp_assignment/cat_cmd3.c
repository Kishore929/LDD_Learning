#include <unistd.h>
#include <fcntl.h>   // for open()
#include <stdlib.h>  // for exit()
#include <stdio.h>   // for perror()

int main(int argc, char *argv[])
{   
    int fd;
    char buf[4096];
    ssize_t nread, nwrite;

    fd = open(argv[1], O_RDONLY);
    if(fd<0){

        perror("Error while opening file");   
        return -1;
    }

    // nread = read(fd, buf, sizeof (buf));

    while((nread = read(fd, buf, sizeof (buf))) > 0 )
    {
        nwrite = write(1, &buf, nread);
        write(1, "\n", 1);

        if (nwrite != nread) {
            perror("Error writing to destination");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }
    
    if (nread < 0) {
        perror("Error while reading file");
    }

    close(fd);
    return 0;
}