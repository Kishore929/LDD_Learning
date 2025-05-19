#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main()
{
int ret;

	ret = write(3,"Hello World\n",5);
	if (ret < 0)
	{
	printf("errono:%d\n",errno);
	perror("Write Fails");
	exit(0);
	}
	printf("errno:%d ret:%d\n",errno,ret);

	return 0;
}

