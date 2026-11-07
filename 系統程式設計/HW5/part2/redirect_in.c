/*
 * redirect_in.c  :  check for <
 */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "shell.h"
#include <string.h>
#include <stdio.h>
#define STD_OUTPUT 1
#define STD_INPUT  0

/*
 * Look for "<" in myArgv, then redirect input to the file.
 * Returns 0 on success, sets errno and returns -1 on error.
 */
int redirect_in(char ** myArgv) {
  	int i = 0;
  	int fd;

  	/* search forward for <
  	 *
	 * Fill in code. */
  	while (myArgv[i] != NULL)
  	{
  		if (strcmp(myArgv[i], "<") == 0)
  			break;
  		i++;
  	}
  	
	if (myArgv[i] == NULL)
  		return 0;
	if (i == 0 || myArgv[i + 1] == NULL)
  		return -1;

  	if (strcmp(myArgv[i], "<") == 0) {	/* found "<" in vector. */

    	/* 1) Open file.
     	 * 2) Redirect stdin to use file for input.
   		 * 3) Cleanup / close unneeded file descriptors.
   		 * 4) Remove the "<" and the filename from myArgv.
		 *
   		 * Fill in code. */
  		fd = open(myArgv[i + 1], O_RDONLY);
  		if (fd == -1)
  			errorMsg("open error");
  		dup2(fd, 0);
  		close(fd);
  		myArgv[i] = NULL;
  	}
  	return 0;
}
