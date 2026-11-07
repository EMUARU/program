/*
 * builtin.c : check for shell built-in commands
 * structure of file is
 * 1. definition of builtin functions
 * 2. lookup-table
 * 3. definition of is_builtin and do_builtin
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include <string.h>




/****************************************************************************/
/* builtin function definitions                                             */
/****************************************************************************/

/* "echo" command.  Does not print final <CR> if "-n" encountered. */
static void bi_echo(char **argv) {
  	/* Fill in code. */
  	int buf = -1;
  	for (int i = 0; argv[i] != NULL; i++) {
  		if (strcmp(argv[i], "-n") == 0) {
  			buf = atoi(argv[i + 1]);
  			break;
  		}
  	}

  	if (buf == -1) {
  		for (int i = 0; argv[i] != NULL; i++) {
	  		if (!strcmp(argv[i], "echo"))
	  			continue;
	  		printf("%s ", argv[i]);
	  	}
	  	printf("\n");
	  	return;
  	}

  	int count = 0;
  	for (int i = 0; argv[i] != NULL; i++) {
  		if (!strcmp(argv[i], "echo") || !strcmp(argv[i], "-n") || !strcmp(argv[i-1], "-n"))
  			continue;

  		count++;
  		if (count == buf)
  			printf("%s\n", argv[i]);
  	}
}
/* Fill in code. */
static void bi_exit() {
	exit(0);
}



/****************************************************************************/
/* lookup table                                                             */
/****************************************************************************/

static struct cmd {
	char * keyword;				/* When this field is argv[0] ... */
	void (* do_it)(char **);	/* ... this function is executed. */
} inbuilts[] = {

	/* Fill in code. */
	{ "quit", bi_exit },
	{ "exit", bi_exit },
	{ "logout", bi_exit },
	{ "bye", bi_exit },

	{ "echo", bi_echo },		/* When "echo" is typed, bi_echo() executes.  */
	{ NULL, NULL }				/* NULL terminated. */
};




/****************************************************************************/
/* is_builtin and do_builtin                                                */
/****************************************************************************/

static struct cmd * this; 		/* close coupling between is_builtin & do_builtin */

/* Check to see if command is in the inbuilts table above.
Hold handle to it if it is. */
int is_builtin(char *cmd) {
  	struct cmd *tableCommand;

  	for (tableCommand = inbuilts ; tableCommand->keyword != NULL; tableCommand++)
    	if (strcmp(tableCommand->keyword,cmd) == 0) {
			this = tableCommand;
			return 1;
		}
  	return 0;
}


/* Execute the function corresponding to the builtin cmd found by is_builtin. */
int do_builtin(char **argv) {
  	this->do_it(argv);
}
