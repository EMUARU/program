#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>

#define BUFFER_SIZE 8192

int indexOf(int size, char *buf[])
{
	int temp;
	for (int i = 1; i < size; i++)
		if (strcmp(buf[i], "-n") == 0)
		{
			temp = atoi(buf[i + 1]);
			if (temp < 0)
				return -1;
			else
				return temp;
		}
	return -1;
}

int main(int argc, char *argv[])
{
	int numRead, option;
	char buf[BUFFER_SIZE];
	memset(buf, '\0', sizeof(buf));
	int fd;
	int num;
	if ((option = getopt(argc, argv, "n")) != -1)
	{
		if ((num = indexOf(argc, argv)) == -1)
		{
			perror("number of line error");
			exit(1);
		}
		fd = open(argv[3], O_RDONLY);
	}
	else
	{
		num = 10;
		fd = open(argv[1], O_RDONLY);
	}

	if (fd == -1)
	{
		perror("open error");
		exit(1);
	}

	int lineCount = 0;
	off_t end = lseek(fd, 0, SEEK_END);

	if (end == -1)
	{
		perror("lseek error 1");
		exit(1);
	}

	end -= 1;
	off_t cur = lseek(fd, -BUFFER_SIZE, SEEK_END);

	if (cur == -1)
		cur = lseek(fd, 0, SEEK_SET);

	int index = 1;

	while ((numRead = read(fd, buf, sizeof(buf))) > 0)
	{
		for (int i = end - cur; i >= 0; i--)
		{
			if (buf[i] == '\n' || lineCount == 0)
				lineCount++;
			if (lineCount == num + 1)
			{
				cur = lseek(fd, cur + i + 1, SEEK_SET);
				if (cur == -1)
				{
					perror("lseek error 2");
					exit(1);
				}
				break;
			}
		}
		if (lineCount == num + 1)
			break;

		index++;
		end = cur;
		cur = lseek(fd, -index * BUFFER_SIZE, SEEK_END);

		if (cur < 0)
			cur = 0;
	}
	end = lseek(fd, 0, SEEK_END);
	if (end == -1)
	{
		perror("lseek error 3");
		exit(1);
	}
	if ((lseek(fd, cur, SEEK_SET)) == -1)
	{
		perror("lseek error 4");
		exit(1);
	}
	int size = end - cur;
	char* r;
	r = (char *)malloc(size * sizeof(char));
	read(fd, r, end - cur);
	write(1, r, size);
	free(r);
	close(fd);
}
