#include <stdio.h>
#include <stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include <signal.h>
#include <unistd.h>



static int alarm_fired = 0;

void ding(int sig)
{
    alarm_fired = 1;
}


int main()
{
    pid_t fork_result;
	int shmid;
	char *msg;
	
	if((shmid=shmget(10,1024,0666|IPC_CREAT))==-1) {
		perror("shmget");
		exit(1);
	}
	
	msg=shmat(shmid,0,0);
	
	fork_result = fork();

        if (fork_result == -1) {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }

		// child process - consumer
	if (fork_result == 0) {
		sleep(1);
		printf("Data written in the shared memory is:%s\n",msg);
		shmdt(msg);
        kill(getppid(), SIGALRM);
        exit(EXIT_SUCCESS);
        }

		// parent prrocess -producer
    else {

		printf("waiting for alarm to go off\n");
    	(void) signal(SIGALRM, ding);

    	printf("Enter the data you want to write into shared memory\n");
		fgets(msg,1024,stdin);
		printf("Data successfully written\n");
		
		if (alarm_fired)
        printf("Ding!\n");

    	printf("done\n");
    	exit(0);		
 	}

}
