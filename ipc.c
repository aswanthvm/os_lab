#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shmfile.txt", 'R');
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    char *shm = shmat(shmid, NULL, 0);

    sprintf(shm, "Shared Memory Content");
    printf("Data Written To Shared Memory\n");

    printf("Data In The SHM: %s\n", shm);

    shmdt(shm);                  // Detach
    shmctl(shmid, IPC_RMID, 0);  // Remove
    return 0;
}
