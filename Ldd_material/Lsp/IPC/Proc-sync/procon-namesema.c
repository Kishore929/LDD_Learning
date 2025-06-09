/******************************************************************************************** 
  WAP producer process and consumer process synchronization using named semaphores.
 *********************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/mman.h>
#include<sys/ipc.h>
#include<sys/shm.h>
sem_t *prod_lock,*cons_lock;
char *msg;
int a,b,n=0,m=0;
pid_t child_pid;

void terminate(int sig)
{
	printf("I got a signal for terminate, for terminate CTRL+C\n");
	sem_unlink("producer1");
	sem_unlink("consumer1");
	signal(SIGINT,SIG_DFL);
}

void main()
{
	signal(SIGINT,terminate);
	prod_lock=sem_open("producer1",O_CREAT,0666,1);
	if(prod_lock==NULL)
	{
		perror("semaphore1");
		exit(0);
	}
	cons_lock=sem_open("consumer1",O_CREAT,0666,0);
	if(cons_lock==NULL)
	{
		perror("semaphore2");
		exit(1);
	}
	sem_getvalue(prod_lock,&a);
	sem_getvalue(cons_lock,&b);
	printf("prod:%d   cons:%d\n",a,b);

	child_pid=fork();
	if(child_pid==0)
	{
		while(1)
		{
			while(n<100)
			{
				sem_wait(prod_lock);
				if(n%2 == 0)
				printf("even:%d\n",n);
				n++;
				sem_post(cons_lock);
			}
			n=0;
		}	

	}
	else
	{
		while(1)
		{
			while(m<100)
			{
				sem_wait(cons_lock);
				if(m%2 == 1) 
				printf("odd :%d\n",m);
				m++;
				sem_post(prod_lock);
			}
			m=0;
		}
	}
}

