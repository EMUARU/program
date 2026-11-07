#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	time_t rawtime;
	struct tm *res;
	time(&rawtime);
	res = localtime(&rawtime);

	char week[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	char month[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
							"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	printf("%s ", month[res->tm_mon]);
	printf("%d", res->tm_mday);
	printf("(%s), ", week[res->tm_wday]); 
	printf("%d ", res->tm_year + 1900);
	printf("%d:", res->tm_hour);
	printf("%d ", res->tm_min);
	printf("%s\n", res->tm_hour >= 12? "PM":"AM");
}