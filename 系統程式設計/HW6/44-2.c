#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 8192

void errorMsg(char *msg)
{
	perror(msg);
	exit(1);
}

int my_pclose(FILE *stream)
{
	if (fclose(stream) == EOF)
		errorMsg("fclose error");
	wait(NULL);
}

FILE *my_popen(char *cmd, char *mode)
{
	char buf[BUFFER_SIZE];
	int pd[2];
	pid_t pid;

	if (pipe(pd) == -1)
		errorMsg("pipe error");

	switch (pid = fork())
	{
	case -1:
		errorMsg("fork error");

	case 0: //child
		if (strcmp(mode, "r") == 0)
		{
			close(pd[0]);
			if (dup2(pd[1], 1) == -1)
				errorMsg("child read mode dup2 error");
			close(pd[1]);
		}
		else if (strcmp(mode, "w") == 0)
		{
			close(pd[1]);
			if (dup2(pd[0], 0) == -1)
				errorMsg("child write mode dup2 error");
			close(pd[0]);
		}

		execl("/bin/sh", "sh", "-c", cmd, (char *)NULL);
		errorMsg("/bin/sh error");

	default:
		if (strcmp(mode, "r") == 0)
			close(pd[1]);
		if (strcmp(mode, "w") == 0)
			close(pd[0]);
	}

	if (strcmp(mode, "r") == 0)
		return fdopen(pd[0], mode);

	if (strcmp(mode, "w") == 0)
		return fdopen(pd[1], mode);
}

int main(int argc, char *argv[])
{
	FILE *fp;
	char line[BUFFER_SIZE];
	int mode;
	printf("### popen and pclose implementation ###\n");
	printf("input mode (1 for read and 2 for write): ");
	scanf("%d", &mode);
	printf("-------------------------------------------\n");
	switch (mode)
	{
	case 1: //read
		fp = my_popen("ls -l", "r");
		if (fp == NULL)
	    	errorMsg("fp error");
		while (fgets(line, sizeof(line), fp) != NULL)
			printf("%s", line);

		break;

	case 2: //write
	    fp = my_popen("wc -l", "w");
	    if (fp == NULL)
	    	errorMsg("fp error");
	    fprintf(fp, "line1\n");
	    fprintf(fp, "line2\n");
	    fprintf(fp, "line3\n");

	    break;

	default:
		errorMsg("mode not found");
	}

    if (my_pclose(fp) == -1)
    	errorMsg("my_pclose error");
}