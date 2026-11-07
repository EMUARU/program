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

#define mxN 1000
#define BUFFER_SIZE 8192

typedef struct Node Node;
typedef struct Data Data;

struct Node
{
	Node* child[mxN];
	int size;
	int depth;
	Node* parent;
	Data* data;
};

struct Data
{
	char pid[mxN];
	char ppid[mxN];
	char name[mxN];
};

void buildTree(Node *root, Data *data);
void buildData(Data *data);
bool findData(char *buf, char *pid, Data *data);
bool isNum(char *buf);
void dfs(Node *root, Data *data, int check);
void freeTree(Node *root);

char* name;
char* ppid;
int sizeAr = 0;

int main()
{
	Node root;

	Data* data;
	data = malloc(mxN * sizeof(Data));
	if (data == NULL)
	{
		perror("data error");
		exit(1);
	}

	name = malloc(mxN * sizeof(char));
	if (name == NULL)
	{
		perror("name error");
		exit(1);
	}

	ppid = malloc(mxN * sizeof(char));
	if (ppid == NULL)
	{
		perror("ppid error");
		exit(1);
	}

	buildData(data);
	buildTree(&root, data);
	dfs(&root, data, 1);

	free(data);
	free(name);
	free(ppid);
	freeTree(&root);
}

void freeTree(Node *root)
{
	if (root->size == 0)
		return;

	if (root->size > 0)
	{
		for (int i = 0; i < root->size; i++)
		{
			freeTree(root->child[i]);
			free(root->child[i]);
		}
	}
}

void dfs(Node *root, Data *data, int check)
{
	Node* cur = root;
	Node* child;
	if (check == 0) //build tree
	{
		for (int i = 0; i < sizeAr; i++)
		{
			if (strcmp(data[i].ppid, cur->data->pid) == 0)
			{
				cur->child[cur->size] = malloc(sizeof(Node));
				if (cur->child[cur->size] == NULL)
				{
					perror("cur->child[cur->size] error");
					exit(1);
				}

				child = cur->child[cur->size];
				for (int i = 0; i < mxN; i++)
					child->child[i] = NULL;
				child->data = &data[i];
				child->parent = cur;
				child->size = 0;
				child->depth = cur->depth + 1;

				cur->child[cur->size] = child;
				cur->size++;
			}
		}
	}
	else if (check == 1) //print tree
	{
		for (int i = 0; i < root->depth; i++)
			printf("   ");

		printf("%s %s\n", root->data->pid, root->data->name);
	}

	if (cur->size == 0)
		return;

	if (cur->size > 0)
        for (int i = 0; i < cur->size; i++)
            dfs(cur->child[i], data, check);
}

void buildTree(Node *root, Data *data)
{
	for (int i = 0; i < sizeAr; i++)
	{
		if (strcmp(data[i].pid, "1") == 0)
		{
			root->data = &data[i];
			for (int i = 0; i < mxN; i++)
				root->child[i] = NULL;
			root->size = 0;
			root->parent = NULL;
			root->depth = 0;
		}
	}
	dfs(root, data, 0);
}

void buildData(Data *data)
{
	DIR* dir = opendir("/proc");

	if (dir == NULL)
	{
		perror("dir open error");
		exit(1);
	}

	struct dirent* ptr;
	char path[mxN];
	int fd;
	int numRead = 0;
	char temp[BUFFER_SIZE];
	int indexData = 0;

	while ((ptr = readdir(dir)) != NULL)
	{
		if (isNum(ptr->d_name) && ptr->d_type == DT_DIR)
		{	
			memset(path, '\0', sizeof(path));
			strcat(path, "/proc/");
			strcat(path, ptr->d_name);
			strcat(path, "/status");

			fd = open(path, O_RDONLY);
			if (fd == -1)
			{
				perror("open error");
				exit(1);
			}

			while ((numRead = read(fd, temp, sizeof(temp))) > 0)
				if (findData(temp, ptr->d_name, &data[indexData]))
				{
					indexData++;
					break;
				}
		}
	}
	closedir(dir);
	close(fd);
}

bool findData(char *buf, char *pid, Data *data)
{
	char* target[] = {"Name", "Uid", "PPid"};
	int check[] = {0, 0, 0}; //Name, Uid, PPid
	char* cp;

	static char delim[] = " \t\n";
	char* token;

	token = strtok(buf, delim);
	if (token == NULL)
		return false;

	while (token != NULL && check[1] != -1)
	{
		if (check[0] == 1) //Name
		{
			strcpy(name, token);
			check[0] = -1;
		}

		if (check[2] == 1) //PPid
		{
			strcpy(ppid, token);
			check[2] = -1;
		}

		if (check[1] == 1) //Uid
		{
			if (atoi(token) >= 0)
			{
				strcpy(data->name, name);
				strcpy(data->pid, pid);
				strcpy(data->ppid, ppid);

				sizeAr++;

				return true;
			}
			check[1] = -1;
		}

		for (int i = 0; i < 3; i++)
		{
			cp = strstr(token, target[i]);
			if (cp != NULL)
				check[i] = 1;
		}

		token = strtok(NULL, delim);
	}
	return false;
}

bool isNum(char *buf)
{
	for (int i = 0; i < strlen(buf); i++)
		if (!isdigit(buf[i]))
			return false;

	return true;
}