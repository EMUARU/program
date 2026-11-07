#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>

#define errExit(x) perror(x), exit(1)
#define MESSAGE "This is message %d"

int bufferSize;
int consumerNum;
int dataSize;

char *name = "/my_shm";

struct SharedData
{
	int index;
	int total;
	int is_full;
	char **queue;
};

struct SharedData *sharedData;

void pop()
{
	while (sharedData->index == 0)
		usleep(10);

	for (int i = 0; i < bufferSize - 1; i++)
		sharedData->queue[i] = sharedData->queue[i + 1];
	
	sharedData->index--;
	sharedData->is_full = 0;
}

void push(char *data)
{
	if (sharedData->is_full)
		pop();

	strcpy(sharedData->queue[sharedData->index], data);
	sharedData->index++;

	if (sharedData->index == bufferSize)
		sharedData->is_full = 1;
}

void handler(int sig, siginfo_t *info, void *context)
{
	int seq = info->si_value.sival_int;

	char data[80];
	sprintf(data, MESSAGE, seq);
	for (int i = 0; i < bufferSize; i++)
	{
		if (strcmp(data, sharedData->queue[i]) == 0)
		{
			sharedData->total++;
			printf("process %d received data: %s\n", getpid(), sharedData->queue[0]);
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc != 5)
	{
		printf("%s [資料數量 M] [傳送速率 R] [consumer數量 N] [buffer size B]\n", argv[0]);
		exit(0);
	}

	dataSize = atoi(argv[1]);
	int sendRate = atoi(argv[2]);
	consumerNum = atoi(argv[3]);
	bufferSize = atoi(argv[4]);

	// shared memory
	int shm_fd;
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	if (shm_fd == -1)
		errExit("shm_open");

	int totalSize = sizeof(struct SharedData) + (bufferSize * 80 * sizeof(char));

	ftruncate(shm_fd, totalSize);

	sharedData = mmap(0, totalSize, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
	if (sharedData == MAP_FAILED)
		errExit("mmap");

	sharedData->index = 0;
	sharedData->total = 0;
	sharedData->is_full = 0;

	sharedData->queue = (char**)((char*)sharedData + sizeof(struct SharedData));
	char* stringsBlock = (char*)sharedData + sizeof(struct SharedData) + (bufferSize * sizeof(char*));
	for (int i = 0; i < bufferSize; i++)
	{
		sharedData->queue[i] = stringsBlock + (i * 80 * sizeof(char));
    	memset(sharedData->queue[i], '\0', 80 * sizeof(char));
	}

	struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);

	pid_t pids[consumerNum];
	for (int i = 0; i < consumerNum; i++)
	{
		switch (pids[i] = fork())
		{
		case -1:
			errExit("fork");

		case 0: // consumer
			while (1)
				pause();
			exit(0);

		default: // producer
			break;
		}
	}

	sleep(2);

	union sigval value;
	for (int i = 0; i < dataSize; i++)
	{
		char data[80];
		sprintf(data, MESSAGE, i);
		push(data);

		printf("%d\n", i);
		push(data);
		for (int j = 0; j < consumerNum; j++)
		{
			value.sival_int = i;
        	if (sigqueue(pids[j], SIGUSR1, value) == -1)
        		errExit("sigqueue");
		}
		usleep(sendRate);
	}

	sleep(2);
	for (int i = 0; i < consumerNum; i++)
		kill(pids[i], SIGKILL);

	for (int i = 0; i < consumerNum; i++)
        waitpid(pids[i], NULL, 0);

    float total = dataSize * consumerNum;
    float loss_rate = 1 - sharedData->total / total;
    printf("Total messages: %3.0f\n", total);
    printf("Sum of received messages by all consumers: %d\n", sharedData->total);
    printf("Loss rate: %6.6f\n", loss_rate);

    munmap(sharedData, totalSize);
    close(shm_fd);
    shm_unlink(name);
}