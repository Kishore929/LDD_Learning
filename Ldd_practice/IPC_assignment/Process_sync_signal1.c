#include <stdio.h>
#include <stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include <signal.h>
#include <unistd.h>


pid_t fork_result;
int shmid;
char *msg;

void con_process(int sig)
{
    printf("Data written in the shared memory is:%s",msg);
	shmdt(msg);
    printf("done\n");

    // exit(EXIT_SUCCESS);
}

void prod_process(int sig)
{
    printf("Enter the data you want to write into shared memory\n");
	fgets(msg,1024,stdin);
	printf("Data successfully written\n");
    kill(fork_result, SIGUSR2);
    exit(EXIT_SUCCESS);
    
}

int main()
{
	
	if((shmid=shmget(10,1024,0666|IPC_CREAT))==-1) {
		perror("shmget");
		exit(1);
	}
	
	msg=shmat(shmid,0,0);
    signal(SIGUSR1, prod_process);

	
	fork_result = fork();

        if (fork_result == -1) {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }

		// child process - consumer
	if (fork_result == 0) {

        signal(SIGUSR2, con_process);
        kill(getppid(), SIGUSR1);

        while(1){
            pause();
        }

        exit(EXIT_SUCCESS);
		// printf("Data written in the shared memory is:%s\n",msg);
		// shmdt(msg);
        
        // exit(EXIT_SUCCESS);
    }

		// parent prrocess -producer
    
    else {
        sleep(1);
        printf("waiting for signal to produce data\n");
        while(1){
            pause();
        }
        
 	}

    return 0;

}
