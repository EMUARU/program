#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define errExit(x) perror(x), exit(1)
typedef void (*sighandler_t)(int);

sighandler_t my_sigset(int sig, sighandler_t disp);
int my_sighold(int sig);
int my_sigrelse(int sig);
int my_sigignore(int sig);
int my_sigpause(int sig);

void handler(int sig)
{
	printf("Signal %d received\n\n", sig);
}

void user_handler(int sig)
{
	if (sig == SIGUSR1)
        printf("User defined signal 1\n");
    if (sig == SIGUSR2)
        printf("User defined signal 2\n");
}

int main(int argc, char* argv[])
{
	int childPid;
	switch (childPid = fork())
	{
	case -1:
		errExit("fork");

	case 0: //child: test system V function
		printf("\033[33m###### System ######\033[0m\n");

		// sigset test
		printf("\033[33m# sigset test #\033[0m\n");
	    sigset(SIGUSR1, handler);
	    raise(SIGUSR1); // send signal

	    // sighold test
	    printf("\033[33m# sighold test #\033[0m\n");
	    sighold(SIGUSR1);
	    raise(SIGUSR1); // shouldn't receive signal
	    printf("\033[33m--- because I send SIGUSR1 during hold, the process shouldn't receive signal ---\033[0m\n\n");

	    sleep(3);

	    // sigrelse test
	    printf("\033[33m# sigrelse test #\033[0m\n");
	    printf("\033[33m--- After relse SIGUSR1, the process will receive a signal that sent in hold time ---\033[0m\n");
	    sigrelse(SIGUSR1);
	    printf("\033[33m--- send SIGUSR1 during relse ---\033[0m\n");
	    raise(SIGUSR1); // receive signal

	    // sigignore test
	    printf("\033[33m# sigignore test #\033[0m\n\n");
	    sigignore(SIGUSR1);
	    raise(SIGUSR1);

	    // sigpause test
	    printf("\033[33m# sigpause test #\033[0m\n");
	    sigset(SIGUSR2, user_handler);

	    struct sigaction sa;
	    sa.sa_handler = handler;
	    sa.sa_flags = 0;
	    sigemptyset(&sa.sa_mask);
	    if (sigaction(SIGUSR1, &sa, NULL) == -1)
	    	errExit("sigaction");

	    sigset_t block_mask, orig_mask;
	    sigemptyset(&block_mask);
	    sigaddset(&block_mask, SIGUSR1);
	    if (sigprocmask(SIG_BLOCK, &block_mask, &orig_mask) == -1)
	    	errExit("sigprocmask");

	    printf("\033[33m--- SIGUSR1 is blocked and waiting for signal SIGUSR1 using sigpause ---\033[0m\n");
	    sleep(7);
	    printf("\033[33m--- sigpause begin ---\033[0m\n");
	    sigpause(SIGUSR1); // wait for signal
	    printf("\033[33m--- sigpause end ---\033[0m\n");
	    sleep(10);

	    sleep(5);
		kill(getppid(), SIGUSR2);
		kill(getppid(), SIGUSR1);
		sleep(5);

	    exit(0);

	default: //parent: test my method
		sleep(5);
		kill(childPid, SIGUSR2);
		kill(childPid, SIGUSR1);
		sleep(5);

		printf("\033[36m###### my method ######\033[0m\n");

		// sigset test
		printf("\033[36m# sigset test #\033[0m\n");
	    my_sigset(SIGUSR1, handler);
	    raise(SIGUSR1); // send signal

	    // sighold test
	    printf("\033[36m# sighold test #\033[0m\n");
	    my_sighold(SIGUSR1);
	    raise(SIGUSR1); // shouldn't receive signal
	    printf("\033[36m--- because I send SIGUSR1 during hold, the process shouldn't receive signal ---\033[0m\n\n");

	    sleep(3);

	    // sigrelse test
	    printf("\033[36m# sigrelse test #\033[0m\n");
	    printf("\033[36m--- After relse SIGUSR1, the process will receive a signal that sent in hold time ---\033[0m\n");
	    my_sigrelse(SIGUSR1);
	    printf("\033[36m--- send SIGUSR1 during relse ---\033[0m\n");
	    raise(SIGUSR1); // receive signal

	    // sigignore test
	    printf("\033[36m# sigignore test #\033[0m\n\n");
	    my_sigignore(SIGUSR1);
	    raise(SIGUSR1);

	    // sigpause test
	    printf("\033[36m# sigpause test #\033[0m\n");
	    my_sigset(SIGUSR2, user_handler);

	    struct sigaction sa1;
	    sa1.sa_handler = handler;
	    sa1.sa_flags = 0;
	    sigemptyset(&sa1.sa_mask);
	    if (sigaction(SIGUSR1, &sa1, NULL) == -1)
	    	errExit("sigaction");

	    sigset_t block_mask1, orig_mask1;
	    sigemptyset(&block_mask1);
	    sigaddset(&block_mask1, SIGUSR1);
	    if (sigprocmask(SIG_BLOCK, &block_mask1, &orig_mask1) == -1)
	    	errExit("sigprocmask");

	    printf("\033[36m--- SIGUSR1 is blocked and waiting for signal SIGUSR1 using sigpause ---\033[0m\n");
	    sleep(7);
	    printf("\033[36m--- sigpause begin ---\033[0m\n");
	    sigpause(SIGUSR1); // wait for signal
	    printf("\033[36m--- sigpause end ---\033[0m\n");
	    sleep(10);
	    wait(NULL);
	    break;
	}
}

sighandler_t my_sigset(int sig, sighandler_t disp)
{
	struct sigaction sa, old;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = disp;

	if (disp == SIG_HOLD)
	{
		sigaddset(&sa.sa_mask, sig);
		if (sigprocmask(SIG_BLOCK, &sa.sa_mask, NULL) == -1)
			return SIG_ERR;
	}

	if (sigaction(sig, &sa, &old) == -1)
		return SIG_ERR;

	return old.sa_handler;
}

int my_sighold(int sig)
{
	sigset_t mSet;
	sigemptyset(&mSet);
	sigaddset(&mSet, sig);
	if (sigprocmask(SIG_BLOCK, &mSet, NULL) == -1)
		return -1;	

	return 0;
}

int my_sigrelse(int sig)
{
	sigset_t mSet;
	sigemptyset(&mSet);
	sigaddset(&mSet, sig);
	if (sigprocmask(SIG_UNBLOCK, &mSet, NULL) == -1)
		return -1;

	return 0;
}

int my_sigignore(int sig)
{
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;

	if (sigaction(sig, &sa, NULL) == -1)
		return -1;

	return 0;
}

int my_sigpause(int sig)
{
	sigset_t mSet;
	sigfillset(&mSet);
	sigdelset(&mSet, sig);

	if (sigsuspend(&mSet) == -1)
		return -1;

	return 0;
}