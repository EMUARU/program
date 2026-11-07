#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define errExit(x) perror(x), exit(1)

int main()
{
	char *fifo_path = "/tmp/my_fifo";
	char buf[1024];
	int numRead, fd;

	if ((fd = open(fifo_path, O_RDONLY | O_NONBLOCK)) == -1)
		errExit("open fifo");

	printf("read message from server: \n");

	while (1)
	{
		numRead = read(fd, buf, sizeof(buf));
		if (numRead > 0)
		{
			write(1, buf, numRead);
			break;
		}
	}

	close(fd);
}