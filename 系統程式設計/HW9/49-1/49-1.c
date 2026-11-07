#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define errExit(x) perror(x), exit(1)

// cp(1) implementation
int main(int argc, char *argv[])
{
	int sourceFd, destFd;
	struct stat statbuf;
	int sourceFileSize;
	void *sourcePtr;
	void *destPtr;

	if (argc != 3 || strcmp(argv[1], "--help") == 0)
	{
		printf("%s [source] [dest]\n", argv[0]);
		if (strcmp(argv[1], "--help") != 0)
			errExit("input");
		exit(0);
	}

	char *sourceFile = argv[1];
	char *desFile = argv[2];

	// open source file and dest file
	sourceFd = open(sourceFile, O_RDONLY);
	destFd = open(desFile, O_RDWR | O_CREAT | O_TRUNC, 0666);

	if (sourceFd < 0)
		errExit("open");

	if (destFd < 0)
		errExit("open");

	// get file size and mmap
	if (fstat(sourceFd, &statbuf) < 0)
	{
		close(sourceFd);
		errExit("fstat");
	}

	sourceFileSize = statbuf.st_size;
	if (sourceFileSize == 0)
	{
		close(destFd);
		munmap(sourcePtr, sourceFileSize);
		close(sourceFd);
		exit(0);
	}

	sourcePtr = mmap(NULL, sourceFileSize, PROT_READ, MAP_PRIVATE, sourceFd, 0);
	if (sourcePtr == MAP_FAILED)
	{
		close(sourceFd);
		errExit("mmap");
	}

	// set file size and mmap
	if (ftruncate(destFd, sourceFileSize) == -1)
	{
		close(destFd);
        munmap(sourcePtr, sourceFileSize);
        close(sourceFd);
        errExit("ftruncate");
	}

	destPtr = mmap(NULL, sourceFileSize, PROT_WRITE, MAP_SHARED, destFd, 0);
	if (destPtr == MAP_FAILED)
	{
		close(destFd);
        munmap(sourcePtr, sourceFileSize);
        close(sourceFd);
		errExit("mmap");
	}

	// copy contents
	memcpy(destPtr, sourcePtr, sourceFileSize);

	munmap(destPtr, sourceFileSize);
    close(destFd);
    munmap(sourcePtr, sourceFileSize);
    close(sourceFd);
}