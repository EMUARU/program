#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

int
main(int argc, char *argv[])
{
    const int SIZE = 4096;
    const char *name = "I_love_Richard";
    const char *semName = "I_love_Richard_Sem";
    int shm_fd;
    void *ptr;
    sem_t *sem;

    // Open the shared memory
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Create a new semaphore
    sem = sem_open(semName, O_CREAT, 0666, 0);

    while (1) {
        char buffer[1024];
        fgets(buffer, 1024, stdin);

        // Write to shared memory
        sprintf(ptr, "%s", buffer);

        // Post (unlock) the semaphore
        sem_post(sem);
    }

    // Close the semaphore
    sem_close(sem);
    sem_unlink(semName);

    return 0;
}
