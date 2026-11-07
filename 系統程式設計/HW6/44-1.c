#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 8192

void errorMsg(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	char buf[BUFFER_SIZE];
	char buf1[BUFFER_SIZE];
	int parentToChild_pd[2];
	int childToParent_pd[2];
	pid_t pid;

	if (pipe(parentToChild_pd) == -1)
		errorMsg("parentToChild_pd error");

	if (pipe(childToParent_pd) == -1)
		errorMsg("childToParent_pd error");

	switch (pid = fork())
	{
	case -1:
		errorMsg("fork error");

	case 0: //child
		close(parentToChild_pd[1]);
		close(childToParent_pd[0]);

		while (1)
		{
			memset(buf, '\0', sizeof(buf));
			if (read(parentToChild_pd[0], buf, sizeof(buf)) == -1)
				errorMsg("child read error");

			for (int i = 0; i < strlen(buf); i++)
				buf[i] = toupper(buf[i]);

			if (write(childToParent_pd[1], buf, strlen(buf)) == -1)
				errorMsg("child write error");
		}

	default: //parent
		close(parentToChild_pd[0]);
		close(childToParent_pd[1]);

		while (fgets(buf1, sizeof(buf1), stdin) != NULL)
		{
			if (write(parentToChild_pd[1], buf1, strlen(buf1)) == -1)
				errorMsg("parent write error");

			memset(buf1, '\0', sizeof(buf1));

			if (read(childToParent_pd[0], buf1, sizeof(buf1)) == -1)
				errorMsg("parent read error");

			if (write(1, buf1, strlen(buf1)) == -1)
				errorMsg("parent write to screen error");
		}

	}
	wait(NULL);
}