/************************************************************************************************************ 
	WAP producer process and consumer process synchronization using Shared Memory, fork() and signals.
*************************************************************************************************************/

#include<unistd.h>
#include<stdio.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<fcntl.h>
#include<signal.h>
#include<stdlib.h>
#include<error.h>

void producer (int  sig);
void consumer(int  sig);
pid_t pid;
int shmid,ret,res;
char * msg;

int main()
{
	shmid=shmget(10,1024,777|IPC_CREAT);
	if(shmid==-1)
	{
		perror("shared memory is failed\n");
		exit(1);
	}
	pid=fork();
	
	if(pid==-1)
	{
		perror("fork is failed\n");
		exit(1);
	}
	if(pid>0)
	{
		signal(SIGALRM,producer);
		msg=shmat(shmid,0,0);
		printf("producer produce the data\n");
		fgets(msg,4096,stdin);
		shmdt(msg);
		kill(pid,SIGALRM);
		printf("produce the is successully \n");
		while(1)
		{
			pause();
		}
		wait(NULL);
	}
	else if(pid==0)
		{
			signal(SIGALRM,consumer);
			while(1)
			{
				pause();
			}
		}
	}

void producer(int sig) 
{
	msg=shmat(shmid,0,0);
	printf("producing the data in the producer\n");
	fgets(msg,4096,stdin);
	shmdt(msg);
	ret=kill(pid,SIGALRM);
	//shmdt(msg);
	if(ret==-1)
	{
		perror("producer is failed to the raise the signal\n");
		exit(1);
	}
	//wait(NULL);
}

void consumer(int sig)
{
	msg=shmat(shmid,0,0);
	printf("consuming the data is %s\n",msg);
	shmdt(msg);
	ret=kill(getppid(),SIGALRM);
	if(ret==-1)
	{
		perror("raising fail\n");
		exit(1);
	}
}

