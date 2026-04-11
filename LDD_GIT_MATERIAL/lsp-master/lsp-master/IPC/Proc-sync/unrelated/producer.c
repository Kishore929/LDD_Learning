#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/mman.h>
//sem_t bin_sem;

int main()
{
	int shmid;
	char* msg;
	char c='A';
	int i=0;
	
	sem_t* sem_empty=sem_open("s2",O_CREAT,O_RDWR,26);
	sem_t* sem_full=sem_open("s3",O_CREAT,O_RDWR,0);

	if(sem_empty==SEM_FAILED)
	{
		perror("sem_empty failed:");
		exit(0);
	}

	if(sem_full==SEM_FAILED)
	{
		perror("sem_full failed:");
		exit(0);
	}

	if((shmid=shmget(12,100,666|IPC_CREAT))==-1) 
         {
            perror("shmget");
            exit(1);
         }


	msg=shmat(shmid,0,0);
	//printf("%d\n",shmid);
	//printf("%p\n",msg);
	if(msg==(void*)-1)
	{
		  perror("shmat:");
		  exit(0);
 	}

//sem_wait(bin_sem);
	while(1)
	{
		sem_wait(sem_empty);
		*(msg+i)=c;
		i=(i+1)%26;
		if(i==0)
		{
			printf("P:%s\n",msg);
			c='A';
		}
		else
		c++;
		sem_post(sem_full);
	}
//printf("P:%s\n",msg);
//sem_post(bin_sem);
 return 0;
}

