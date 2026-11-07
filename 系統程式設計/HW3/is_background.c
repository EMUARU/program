/*
 * is_background.c :  check for & at end
 */


#include <stdio.h>
#include "shell.h"
#include <string.h>

int is_background(char ** myArgv) {

  	if (*myArgv == NULL)
    	return 0;

  	/* Look for "&" in myArgv, and process it.
  	 *
	 *	- Return TRUE if found.
	 *	- Return FALSE if not found.
	 *
	 * Fill in code.
	 */
    for (int i = 0; myArgv[i] != NULL; i++)
    	if (strcmp(myArgv[i], "&") == 0)
    		return TRUE;

    return FALSE;
}