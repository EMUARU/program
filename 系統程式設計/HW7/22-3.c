#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

static void handler(int sig)
{
}

#define TESTSIG SIGUSR1
#define errExit(x) perror(x), exit(1)
#define usageErr(x, y) printf(x, y), exit(0)

void sigsuspendFunc(int numSigs)
{
    int scnt;
    pid_t childPid;
    sigset_t blockedMask, emptyMask;
    struct sigaction sa;

    clock_t start, end;
    double cpu_time_used;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigaction(TESTSIG, &sa, NULL) == -1)
        errExit("sigaction");

    /* Block the signal before fork(), so that the child doesn't manage
       to send it to the parent before the parent is ready to catch it */

    sigemptyset(&blockedMask);
    sigaddset(&blockedMask, TESTSIG);
    if (sigprocmask(SIG_SETMASK, &blockedMask, NULL) == -1)
        errExit("sigprocmask");

    sigemptyset(&emptyMask);

    switch (childPid = fork())
    {
    case -1:
        errExit("fork");

    case 0:     /* child */
        for (scnt = 0; scnt < numSigs; scnt++)
        {
            if (kill(getppid(), TESTSIG) == -1)
                errExit("kill");
            if (sigsuspend(&emptyMask) == -1 && errno != EINTR)
                errExit("sigsuspend");
        }
        exit(0);

    default: /* parent */
        start = clock();
        for (scnt = 0; scnt < numSigs; scnt++)
        {
            if (sigsuspend(&emptyMask) == -1 && errno != EINTR)
                errExit("sigsuspend");
            if (kill(childPid, TESTSIG) == -1)
                errExit("kill");
        }
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf(" sigsuspend time in second: %f\n", cpu_time_used);
        wait(NULL);
        break;
    }
}

void sigwaitinfoFunc(int numSigs)
{
    int scnt;
    pid_t childPid;
    sigset_t blockedMask;
    siginfo_t info;
    int sig;
    struct sigaction sa;

    clock_t start, end;
    double cpu_time_used;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigaction(TESTSIG, &sa, NULL) == -1)
        errExit("sigaction");

    /* Block the signal before fork(), so that the child doesn't manage
       to send it to the parent before the parent is ready to catch it */

    sigemptyset(&blockedMask);
    sigaddset(&blockedMask, TESTSIG);
    if (sigprocmask(SIG_SETMASK, &blockedMask, NULL) == -1)
        errExit("sigprocmask");

    switch (childPid = fork())
    {
    case -1:
        errExit("fork");

    case 0:     /* child */
        for (scnt = 0; scnt < numSigs; scnt++)
        {
            if (kill(getppid(), TESTSIG) == -1)
                errExit("kill");
            if (sigwaitinfo(&blockedMask, &info) == -1)
                errExit("sigwaitinfo");
        }
        exit(0);

    default: /* parent */
        start = clock();
        for (scnt = 0; scnt < numSigs; scnt++)
        {
            if (sigwaitinfo(&blockedMask, &info) == -1)
                errExit("sigwaitinfo");
            if (kill(childPid, TESTSIG) == -1)
                errExit("kill");
        }
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("sigwaitinfo time in second: %f\n", cpu_time_used);
        wait(NULL);
        break;
    }
}

int main(int argc, char *argv[])
{
    int numSigs;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s num-sigs\n", argv[0]);

    numSigs = atoi(argv[1]);

    sigsuspendFunc(numSigs);
    sigwaitinfoFunc(numSigs);
}
