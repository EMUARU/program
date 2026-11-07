#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>

int* outputFDs;
int size;

void handleCtrlC(int signal)
{
	for (int i = 0; i < size; i++)
		close(outputFDs[i]);
	free(outputFDs);
	printf("\n");
	exit(0);
}

int main(int argc, char *argv[])
{
	int numRead, option;

	signal(SIGINT, handleCtrlC);

	if ((option = getopt(argc, argv, "a")) != -1)
	{
		size = argc - 2;
		outputFDs = (int*)malloc(size * sizeof(int));
		for (int i = 1, j = 0; i < argc; i++)
		{
			if (strcmp(argv[i], "-a") == 0)
				continue;

			outputFDs[j] = open(argv[i], O_RDWR | O_CREAT | O_APPEND, 0666);
			if (outputFDs[j] == -1)
				perror("outputFDs failure");
			j++;
		}
	}
	else
	{
		size = argc - 1;
		outputFDs = (int*)malloc(size * sizeof(int));

		for (int i = 1; i < argc; i++)
		{
			outputFDs[i-1] = open(argv[i], O_RDWR | O_CREAT | O_TRUNC, 0666);
			if (outputFDs[i-1] == -1)
				perror("outputFDs failure");
		}
	}
	while (1)
	{
		char buf[1000];
		numRead = read(0, buf, 1000);

		for (int i = 0; i < size; i++)
			write(outputFDs[i], buf, numRead);

		write(1, buf, numRead);
	}

}
