#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void errorMsg(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	long pathmaxlen = pathconf(".", _PC_PATH_MAX);

	if (pathmaxlen == -1)
		errorMsg("pathconf error");

	char *cwd = malloc(pathmaxlen + 1);
	if (cwd == NULL)
		errorMsg("malloc error");

	cwd = getcwd(NULL, pathmaxlen + 1);
	if (cwd == NULL)
		errorMsg("getcwd error");

	printf("%s\n", cwd);
	free(cwd);
}