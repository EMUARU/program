#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 8192

void errorMsg(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	char *command[] = {"ls", "-l", NULL};
	char buf[BUFFER_SIZE];
	int pd[2];
	pid_t pid;

	if (pipe(pd) == -1)
		errorMsg("pipe error");

	int readFd = pd[0];
	int writeFd = pd[1];

	switch (pid = fork())
	{
	case -1:
		errorMsg("fork error");

	case 0: //child
		close(readFd);
		dup2(writeFd, 1);
		close(writeFd);
		if (execvp(command[0], command) == -1)
			errorMsg("execvp error");

	default:
		break;
	}

	close(writeFd);
	while (read(readFd, buf, sizeof(buf)) > 0)
		printf("%s", buf);
	close(readFd);

	wait(NULL);
}