
#include<unistd.h>
#include<stdio.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<fcntl.h>
#include<signal.h>
#include<stdlib.h>
#include<error.h>

void consumer(int  sig);
pid_t pid;
int shmid,ret,res;
char * msg;

int main()
{
	shmid=shmget(10,1024,0);
	if(shmid==-1) {
		perror("shared memory is failed\n");
		exit(1);
		}
	
	signal(SIGALRM,consumer);		//Handle the signal

	while(1){
			pause();
		}
}
	
void consumer(int sig)
{
	msg=shmat(shmid,0,0);
	printf("consuming the data is %s\n",msg);
	shmdt(msg);
	ret=kill(getppid(),SIGALRM);		//Rise a signal
	if(ret==-1){
		perror("raising fail\n");
		exit(1);
		}
}


