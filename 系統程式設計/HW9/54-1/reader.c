#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
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
    shm_fd = shm_open(name, O_RDONLY, 0666);
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    // Open the semaphore
    sem = sem_open(semName, 0);

    while (1) {
        // Wait (lock) the semaphore
        sem_wait(sem);

        // Read from shared memory
        printf("%s", (char *)ptr);
    }

    // Close the semaphore
    sem_close(sem);

    return 0;
}
