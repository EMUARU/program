#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define errExit(x) perror(x), exit(1)

int main()
{
	char *fifo_path = "/tmp/my_fifo";
	int fd;

	if (mkfifo(fifo_path, 0666) == -1)
		errExit("mkfifo");

	if ((fd = open(fifo_path, O_WRONLY | O_NONBLOCK)) == -1)
		printf("failed: client doesn't open the fifo\n");

	printf("wait 10 seconds for client to open the fifo\n");
	sleep(10);
	if ((fd = open(fifo_path, O_WRONLY | O_NONBLOCK)) == -1)
	{	
		unlink(fifo_path);
		errExit("client still doesn't open the fifo");
	}

	printf("client successfully open the fifo!\n");

	char *msg = "Hello, I am server!\n";

	if (write(fd, msg, strlen(msg)) == -1)
	{
		unlink(fifo_path);
		errExit("write");
	}

	printf("successfully send the message\n");

	close(fd);
	unlink(fifo_path);
}