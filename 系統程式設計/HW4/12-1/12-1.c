#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define mxN 100
#define BUFFER_SIZE 1024

uid_t userIdFromName(const char *name);
bool isNum(char *buf);
bool findNameUid(char *buf, char *pid, uid_t uid);

char* temp1;
char* bufUid;

int main(int argc, char *argv[])
{	
	temp1 = malloc(50 * sizeof(char));
	bufUid = malloc(20 * sizeof(char));
	if (argc != 2)
	{
		perror("read argv error");
		exit(1);
	}

	uid_t uid = userIdFromName(argv[1]);

	char* path = "/proc";

	DIR* dir = opendir(path);

	if (dir == NULL)
	{
		perror("dir open error");
		exit(1);
	}

	struct dirent* ptr;

	char path1[mxN];
	int fd;
	int numRead = 0;
	char temp[BUFFER_SIZE];
	memset(temp, '\0', sizeof(temp));

	while ((ptr = readdir(dir)) != NULL)
	{
		if (isNum(ptr->d_name) && ptr->d_type == DT_DIR)
		{	
			memset(path1, '\0', sizeof(path1));
			strcat(path1, "/proc/");
			strcat(path1, ptr->d_name);
			strcat(path1, "/status");

			fd = open(path1, O_RDONLY);
			if (fd == -1)
			{
				perror("open error");
				exit(1);
			}
			while ((numRead = read(fd, temp, sizeof(temp))) > 0)
				if (findNameUid(temp, ptr->d_name, uid))
					break;
		}
	}

	closedir(dir);
	close(fd);
	free(temp1);
	free(bufUid);
}

uid_t userIdFromName(const char *name)
{
	struct passwd *pwd;
	uid_t u;
	char *endptr;

	if (name == NULL || *name == '\0')
		return -1;

	u = strtol(name, &endptr, 10);

	if (*endptr == '\0')
		return u;

	pwd = getpwnam(name);

	if (pwd == NULL)
		return -1;

	return pwd->pw_uid;
}

bool isNum(char *buf)
{
	for (int i = 0; i < strlen(buf); i++)
		if (!isdigit(buf[i]))
			return false;

	return true;
}

bool findNameUid(char *buf, char *pid, uid_t uid)
{
	char* target[] = {"Name", "Uid"};
	int check[] = {0, 0}; //Name, Uid
	char* cp;
	sprintf(bufUid, "%d",uid);

	static char delim[] = " \t\n";
	char* token;

	token = strtok(buf, delim);
	if (token == NULL)
		return false;

	while (token != NULL && check[1] != -1)
	{
		if (check[0] == 1)
		{
			strcpy(temp1, token);
			check[0] = -1;
		}

		if (check[1] == 1)
		{
			if (strcmp(bufUid, token) == 0)
			{
				printf("%s ", pid);
				if (temp1 != NULL)
					printf("%s\n", temp1);

				return true;
			}
			check[1] = -1;
		}

		for (int i = 0; i < 2; i++)
		{
			cp = strstr(token, target[i]);
			if (cp != NULL)
				check[i] = 1;
		}

		token = strtok(NULL, delim);
	}
	return false;
}