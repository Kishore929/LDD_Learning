#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/mman.h>

typedef struct {
    sem_t empty;
    sem_t full;
    char buffer[26];
} Shared;

int main() {
    Shared *shm = mmap(NULL, sizeof(Shared), PROT_READ | PROT_WRITE,
                       MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (shm == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    sem_init(&shm->empty, 1, 26); // 26 empty slots initially
    sem_init(&shm->full, 1, 0);   // 0 full slots initially

    pid_t fork_result = fork();

    if (fork_result < 0) {
        perror("fork");
        exit(1);
    }

    if (fork_result == 0) {
        // Consumer
        int out = 0;
        for (int i = 0; i < 26; i++) {
            sem_wait(&shm->full);
            char item = shm->buffer[out];
            printf("Consumer: Read '%c' at index %d\n", item, out);
            out = (out + 1) % 26;
            sem_post(&shm->empty);
            usleep(100000); // optional small delay
        }
        printf("Consumer: Finished reading A-Z. Exiting.\n");
        exit(0);
    } else {
        // Producer
        int in = 0;
        char item = 'A';
        for (int i = 0; i < 26; i++) {
            sem_wait(&shm->empty);
            shm->buffer[in] = item;
            printf("Producer: Wrote '%c' at index %d\n", item, in);
            in = (in + 1) % 26;
            sem_post(&shm->full);
            item++;
            usleep(100000); // optional small delay
        }
        printf("Producer: Finished writing A-Z. Exiting.\n");
        exit(0);
    }

    return 0;
}



/*


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>      // For O_CREAT, O_EXCL
#include <semaphore.h>  // For sem_t, sem_open, sem_wait, etc.
#include <string.h>
#include <sys/wait.h>

#define SIZE 26

int main() {
    int shmid;
    char *buffer;

    // Create shared memory
    shmid = shmget(IPC_PRIVATE, SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    // Create named semaphores
    sem_t *empty = sem_open("/sem_empty", O_CREAT | O_EXCL, 0666, SIZE);
    sem_t *full  = sem_open("/sem_full",  O_CREAT | O_EXCL, 0666, 0);
    if (empty == SEM_FAILED || full == SEM_FAILED) {
        perror("sem_open failed");
        shmctl(shmid, IPC_RMID, NULL); // Clean up shared memory
        exit(1);
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Consumer process
        buffer = (char *)shmat(shmid, NULL, 0);

        for (int i = 0; i < SIZE; i++) {
            sem_wait(full); // Wait until there's something to consume
            printf("Consumer read: %c\n", buffer[i]);
            sem_post(empty); // Signal there's space for more
        }

        shmdt(buffer);
        exit(0);
    } else {
        // Producer process
        buffer = (char *)shmat(shmid, NULL, 0);

        for (int i = 0; i < SIZE; i++) {
            sem_wait(empty); // Wait until there's space
            buffer[i] = 'A' + i;
            printf("Producer wrote: %c\n", buffer[i]);
            sem_post(full); // Signal data is available
        }

        shmdt(buffer);
        wait(NULL); // Wait for child to finish

        // Cleanup
        shmctl(shmid, IPC_RMID, NULL);
        sem_unlink("/sem_empty");
        sem_unlink("/sem_full");
        sem_close(empty);
        sem_close(full);

        exit(0);
    }
}




*/