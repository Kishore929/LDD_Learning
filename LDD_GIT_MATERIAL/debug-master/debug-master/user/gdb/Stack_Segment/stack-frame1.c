#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main (void)
{
	unsigned int stackVar = 3;
	char szCommand[64];

	printf (" Address of stackVar is 0x%p\n\n", &stackVar);
	sprintf (szCommand, "cat /proc/%d/maps", getpid() );
	system (szCommand);

	return 0;
}
