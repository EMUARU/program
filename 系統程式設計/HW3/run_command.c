/*
 * run_command.c :    do the fork, exec stuff, call other functions
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include "shell.h"
#include <unistd.h>
#include <string.h>

void run_command(char **myArgv) {
    pid_t pid;
    int stat;

    /* Create a new child process.
     * Fill in code.
	 */
    pid = fork();

    switch (pid) {

        /* Error. */
        case -1 :
            perror("fork");
            exit(errno);

        /* Parent. */
        default :
            /* Wait for child to terminate.
             * Fill in code.
			 */
            if (!is_background(myArgv))
                waitpid(pid, &stat, 0);

            /* Optional: display exit status.  (See wstat(5).)
             * Fill in code.
			 */

            return;

        /* Child. */
        case 0 :
            /* Run command in child process.
             * Fill in code.
			 */
            if (!is_background(myArgv))
                execvp(myArgv[0], myArgv);
            else {
                for (int i = 0; myArgv[i] != NULL; i++) {
                    if (strcmp(myArgv[i], "&") == 0) {
                        myArgv[i] = NULL;
                        break;
                    }
                }
                execvp(myArgv[0], myArgv);
            }


            /* Handle error return from exec */
			exit(errno);
    }
}
