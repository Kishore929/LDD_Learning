#include <unistd.h>
#include <fcntl.h>  
#include <string.h>  // for strlen()



int main(int argc, char *argv[])
{
    if (argc < 2) {
        write(2, "Usage: ./a.out <string>\n", 25);
        return 1;
    }
    
    write(1, argv[1], strlen(argv[1]));
    write(1, "\n", 1);
    return 0;
}