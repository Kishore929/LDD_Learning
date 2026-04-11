/****************************************************************************************************************** 
	WAP producer process and consumer process synchronization using Shared Memory, fork() and named semaphores.
*******************************************************************************************************************/

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
int a,b;
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
            a=shmget(16,1024,IPC_CREAT|0666);
            if(a<0)
            {
                perror("shmget");
                exit(2);
            }
    child_pid=fork();
    if(child_pid==0)
    {
        while(1)
        {
            sem_wait(prod_lock);
            msg=shmat(a,0,0);
            if(msg==NULL)
            {
                perror("shmat");
                exit(3);
            }
            printf("Enter a msg:");
            fgets(msg,1024,stdin);
            shmdt(msg);
            sem_post(cons_lock);
        }
    }
    else
    {
        while(1)
        {
            sem_wait(cons_lock);
            msg=shmat(a,0,0);
            if(msg==NULL)
            {
                perror("shmat");
                exit(5);
            }
            printf("Msg is:%s\n",msg);
            shmdt(msg);
            sem_post(prod_lock);
        }
    }
}

