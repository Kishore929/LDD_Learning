#include <stdio.h>
#include <unistd.h> 

int main() {
    int c;
    ssize_t nread;
    char buf[1024];

    nread = read(0, buf, 1);

    if(nread > 0){
        write(1, buf, nread);
        write(1, "\n", 1);
    }

    return 0;
}
