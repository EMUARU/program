#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>

#define mxN 1000
#define BUFFER_SIZE 8192

char* scan(char *path);
char* findName(char *pid);
bool isNum(char *buf);

char ansPid[mxN][mxN];
char ansName[mxN][mxN];
int index1 = 0;


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		perror("input error");
		exit(1);
	}

	scan(argv[1]);

	for (int i = 0; i < index1; i++)
		printf("%s %s\n", ansPid[i], ansName[i]);
}

char* scan(char *target)
{
	DIR* dir = opendir("/proc");

	if (dir == NULL)
	{
		perror("dir open error");
		exit(1);
	}

	struct dirent* ptr;
	struct dirent* ptr1;
	char path[mxN];
	char path1[mxN];

	while ((ptr = readdir(dir)) != NULL)
	{
		if (isNum(ptr->d_name) && ptr->d_type == DT_DIR)
		{	
			memset(path, '\0', sizeof(path));
			strcat(path, "/proc/");
			strcat(path, ptr->d_name);
			strcat(path, "/fd");

			char* name = findName(ptr->d_name);

			DIR* dir1 = opendir(path);

			if (dir1 == NULL)
				continue;

			char buf[mxN];
			int len;
			bool checkSame = 0;

			while ((ptr1 = readdir(dir1)) != NULL)
			{
				if (isNum(ptr1->d_name))
				{
					memset(path1, '\0', sizeof(path1));
					strcat(path1, "/proc/");
					strcat(path1, ptr->d_name);
					strcat(path1, "/fd/");
					strcat(path1, ptr1->d_name);

					len = readlink(path1, buf, sizeof(buf) - 1);

					if (len == -1)
					{
						perror("readlink error");
						exit(1);
					}

					buf[len] = '\0';

					if (strcmp(target, buf) == 0)
					{
						for (int i = 0; i < index1; i++)
							if (strcmp(ansPid[i], ptr->d_name) == 0)
								checkSame = 1;

						if (!checkSame)
						{
							strcpy(ansPid[index1], ptr->d_name);
							strcpy(ansName[index1], name);
							index1++;
							checkSame = 0;
						}
					}
				}
			}
			closedir(dir1);
		}
	}
	closedir(dir);
}

char* findName(char *pid)
{
	char path[mxN];
	memset(path, '\0', sizeof(path));
	strcat(path, "/proc/");
	strcat(path, pid);
	strcat(path, "/status");

	int fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("open error");
		exit(1);
	}

	int numRead = 0;
	char buf[BUFFER_SIZE];

	static char delim[] = " \t\n";
	char* token;
	char* cp;
	bool check = 0;

	while ((numRead = read(fd, buf, sizeof(buf))) > 0)
	{
		token = strtok(buf, delim);
		if (token == NULL)
			return false;

		while (token != NULL)
		{
			if (check == 1)
				return token;

			cp = strstr(token, "Name");
			if (cp != NULL)
				check = 1;

			token = strtok(NULL, delim);
		}
	}
	return NULL;
}

bool isNum(char *buf)
{
	for (int i = 0; i < strlen(buf); i++)
		if (!isdigit(buf[i]))
			return false;

	return true;
}