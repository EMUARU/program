/*
 * parse.c : use whitespace to tokenise a line
 * Initialise a vector big enough
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include <errno.h>

/* Parse a commandline string into an argv array. */
char ** parse(char *line) {

  	static char delim[] = " \t\n"; /* SPACE or TAB or NL */
  	int count = 0;
  	char * token;
  	char **newArgv;

  	/* Nothing entered. */
  	if (line == NULL) {
    	return NULL;
  	}

  	/* Init strtok with commandline, then get first token.
     * Return NULL if no tokens in line.
	 *
	 * Fill in code.
     */
     token = strtok(line, delim);
     if (token == NULL)
     	return NULL;


  	/* Create array with room for first token.
  	 *
	 * Fill in code.
	 */
     count++;
     newArgv = NULL;
     newArgv = (char **)realloc(newArgv, count * sizeof(char *));
     if (newArgv == NULL) {
     	perror("newArgv error");
     	exit(1);
     }

  	/* While there are more tokens...
	 *
	 *  - Get next token.
	 *	- Resize array.
	 *  - Give token its own memory, then install it.
	 * 
  	 * Fill in code.
	 */
     for (int i = 0; token != NULL; i++) {
     	if (i != 0) {
     		count++;
     		newArgv = (char **)realloc(newArgv, count * sizeof(char *));
     		if (newArgv == NULL) {
		     	perror("newArgv 1 error");
		     	exit(1);
		     }
     	}
     	newArgv[i] = NULL;
     	newArgv[i] = (char *)realloc(newArgv[i], (strlen(token) + 1) * sizeof(char));
     	if (newArgv[i] == NULL) {
	     	perror("newArgv[] error");
	     	exit(1);
	     }
	    	strcpy(newArgv[i], token);
	    	printf("[%d] : %s\n", i, newArgv[i]);
	     
	    	token = strtok(NULL, delim);
     }


  	/* Null terminate the array and return it.
	 *
  	 * Fill in code.
	 */
     count++;
     newArgv = (char **)realloc(newArgv, count * sizeof(char *));
     if (newArgv == NULL) {
     	perror("newArgv 2 error");
     	exit(1);
     }
     newArgv[count - 1] = NULL;

  	return newArgv;
}


/*
 * Free memory associated with argv array passed in.
 * Argv array is assumed created with parse() above.
 */
void free_argv(char **oldArgv) {

	int i = 0;

	/* Free each string hanging off the array.
	 * Free the oldArgv array itself.
	 *
	 * Fill in code.
	 */
	for (; oldArgv[i] != NULL; i++)
		free(oldArgv[i]);
	free(oldArgv);
}
