/*
 * builtin.c : check for shell built-in commands
 * structure of file is
 * 1. definition of builtin functions
 * 2. lookup-table
 * 3. definition of is_builtin and do_builtin
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <sys/utsname.h>
#include "shell.h"
#include <string.h>

/****************************************************************************/
/* builtin function definitions                                             */
/****************************************************************************/
static void bi_builtin(char ** argv);	/* "builtin" command tells whether a command is builtin or not. */
static void bi_cd(char **argv) ;		/* "cd" command. */
static void bi_echo(char **argv);		/* "echo" command.  Does not print final <CR> if "-n" encountered. */
static void bi_hostname(char ** argv);	/* "hostname" command. */
static void bi_id(char ** argv);		/* "id" command shows user and group of this process. */
static void bi_pwd(char ** argv);		/* "pwd" command. */
static void bi_quit(char **argv);		/* quit/exit/logout/bye command. */




/****************************************************************************/
/* lookup table                                                             */
/****************************************************************************/

static struct cmd {
  	char * keyword;					/* When this field is argv[0] ... */
  	void (* do_it)(char **);		/* ... this function is executed. */
} inbuilts[] = {
  	{ "builtin",    bi_builtin },   /* List of (argv[0], function) pairs. */

    /* Fill in code. */
    { "echo",       bi_echo },
    { "quit",       bi_quit },
    { "exit",       bi_quit },
    { "bye",        bi_quit },
    { "logout",     bi_quit },
    { "cd",         bi_cd },
    { "pwd",        bi_pwd },
    { "id",         bi_id },
    { "hostname",   bi_hostname },
    {  NULL,        NULL }          /* NULL terminated. */
};

void errorMsg(char *msg)
{
    perror(msg);
    exit(1);
}

static void bi_builtin(char ** argv) {
	/* Fill in code. */

    if (is_builtin(argv[1]) == 1)
        printf("%s is a builtin feature.\n", argv[1]);
    else
        printf("%s is NOT a builtin feature.\n", argv[1]);
}

static void bi_cd(char **argv) {
	/* Fill in code. */
    if (chdir(argv[1]) == -1)
        errorMsg("chdir error");
}

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

static void bi_hostname(char ** argv) {
	/* Fill in code. */
    struct utsname uts;

    if (uname(&uts) == -1)
        errorMsg("uname error");

    long host_id = gethostid();

    printf("hostname: %s\n", uts.nodename);
}

static void bi_id(char ** argv) {
 	/* Fill in code. */
    uid_t uid = getuid();
    gid_t gid = getgid();
    struct passwd *userInfo = getpwuid(uid);

    printf("UserID = %d(%s), GroupID = %d(%s)\n", uid, userInfo->pw_name, gid, userInfo->pw_name);
}

static void bi_pwd(char ** argv) {
	/* Fill in code. */
    long pathmaxlen = pathconf(".", _PC_PATH_MAX);

    if (pathmaxlen == -1)
        errorMsg("pathconf error");

    char *cwd = malloc(pathmaxlen + 1);
    if (cwd == NULL)
        errorMsg("malloc error");

    cwd = getcwd(NULL, pathmaxlen + 1);
    if (cwd == NULL)
        errorMsg("getcwd error");

    printf("%s\n", cwd);
    free(cwd);
}

static void bi_quit(char **argv) {
	exit(0);
}


/****************************************************************************/
/* is_builtin and do_builtin                                                */
/****************************************************************************/

static struct cmd * this; /* close coupling between is_builtin & do_builtin */

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
