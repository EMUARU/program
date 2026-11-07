#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>

int main(int argc, char *argv[])
{
	int readFd, writeFd;
	size_t numRead, numWrite;
	char buf[1];
	struct stat oriState;

	stat(argv[1], &oriState);

	readFd = open(argv[1], O_RDONLY);

	if (readFd == -1)
		perror("readFd failure");

	writeFd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);

	if (writeFd == -1)
		perror("writeFd failure");

	while((numRead = read(readFd, buf, 1)) > 0)
	{
		if (buf[0] == 0x00)
		{
			//printf("Read a null byte (0x00).\n");
			lseek(writeFd, 1, SEEK_CUR);
			continue;
		}
		numWrite = write(writeFd, buf, numRead);
	}
	chmod(argv[2], oriState.st_mode);

	if (readFd != -1)
		close(readFd);
	if (writeFd != -1)
		close(writeFd);
}
