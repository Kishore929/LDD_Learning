#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

void testfunc (int a, int b, int c, int d)
{
char flag=0xff;
char buffer[10];
memset (buffer, 0xae, 10);
}

int main()
{
testfunc (1, 2, 3, 4);
exit (0);
}
