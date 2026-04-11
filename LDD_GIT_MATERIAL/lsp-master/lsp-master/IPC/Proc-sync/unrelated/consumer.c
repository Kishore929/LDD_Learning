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
	sem_t* sem_empty=sem_open("s2",O_EXCL,O_RDWR);
	sem_t* sem_full=sem_open("s3",O_EXCL,O_RDWR);
	char c ='A';
	char* msg;
	int shmid;
	int i=0;
	char buff[26];
	if((shmid=shmget(12,100,666))==-1) 
         {
            perror("shmget");
            exit(1);
         }
	msg=shmat(shmid,0,0);
	//printf("%d\n",shmid);
	//printf("%p\n",msg);
	while(1)
	{
		sem_wait(sem_full);
		buff[i]=*(msg+i);
		i=(i+1)%26;
		if(i==0)
		{
			printf("C:%s\n",msg);
		}
		sem_post(sem_empty);
	}
	 return 0;
}

