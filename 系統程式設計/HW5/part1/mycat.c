#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 8192

void errorMsg(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: mycat filename\n");
		return 0;
	}

	char buf[BUFFER_SIZE];
	int numRead;
	int fd = open(argv[1], O_RDONLY);

	if (fd == -1)
		errorMsg("open error");


	while ((numRead = read(fd, buf, sizeof(BUFFER_SIZE))) > 0)
		write(1, buf, numRead);

	close(fd);
}