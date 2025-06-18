
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h> /* ioctl() */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h> /* EVIOCGNAME - /usr/include/linux/input.h */

// To get input device name

main()
{
	int fd,ret;
	char len[30];
	fd = open("/dev/input/event0",O_RDONLY);
	if (fd < 0)
	{
		perror("open fail");
		exit(0);
	}

	ret = ioctl(fd,EVIOCGNAME(sizeof(len)),len);
	if (ret < 0)
		perror("ioctl fail");
	printf("dev name:%s\n",len);
}
