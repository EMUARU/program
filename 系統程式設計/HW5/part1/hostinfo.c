#include <sys/utsname.h>
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
	struct utsname uts;

	if (uname(&uts) == -1)
		errorMsg("uname error");

	long host_id = gethostid();

	printf("hostname: %s\n", uts.nodename);
	printf("%s\n", uts.release);
	printf("hostid: %lx\n", host_id);
}