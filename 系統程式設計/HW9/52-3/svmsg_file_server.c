/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 46-8 */

#include "svmsg_file.h"

static void             /* SIGCHLD handler */
grimReaper(int sig)
{
    int savedErrno;

    savedErrno = errno;                 /* waitpid() might change 'errno' */
    while (waitpid(-1, NULL, WNOHANG) > 0)
        continue;
    errno = savedErrno;
}

static void
removeQueue(void)
{
    mq_unlink("/client_queue");
    mq_unlink("/server_queue");
}

static void             /* Executed in child process: serve a single client */
serveRequest(const struct requestMsg *req)
{
    int fd;
    ssize_t numRead;
    struct responseMsg resp;

    mqd_t mq_client_queue;

    fd = open(req->pathname, O_RDONLY);
    if (fd == -1)
        exit(EXIT_FAILURE);

    /* Transmit file contents in messages with type RESP_MT_DATA. We don't
       diagnose read() and msgsnd() errors since we can't notify client. */

    resp.mtype = RESP_MT_DATA;

    mq_client_queue  = mq_open("/client_queue", O_RDWR);
    if (mq_client_queue == (mqd_t)-1)
        errExit("mq_open");

    while ((numRead = read(fd, resp.data, RESP_MSG_SIZE)) > 0)
        if (mq_send(mq_client_queue, (char *)&resp, numRead + sizeof(resp.mtype), 0) == -1)
            errExit("mq_send");

    /* Send a message of type RESP_MT_END to signify end-of-file */

    resp.mtype = RESP_MT_END;
    if (mq_send(mq_client_queue, (char *)&resp, sizeof(int), 0) == -1)
        errExit("mq_send 1");
}

int
main(int argc, char *argv[])
{
    struct requestMsg req;
    pid_t pid;
    struct sigaction sa;

    if (atexit(removeQueue) != 0)
        errExit("atexit");

    mqd_t mq_server_queue;
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(struct requestMsg);
    attr.mq_curmsgs = 0;

    mq_server_queue  = mq_open("/server_queue", O_CREAT | O_RDWR, 0644, &attr);
    if (mq_server_queue == (mqd_t)-1)
        errExit("mq_open");

    /* Establish SIGCHLD handler to reap terminated children */

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = grimReaper;
    if (sigaction(SIGCHLD, &sa, NULL) == -1)
        errExit("sigaction");

    /* Read requests, handle each in a separate child process */

    for (;;) {
        if (mq_receive(mq_server_queue, (char *)&req, sizeof(struct requestMsg), NULL) == -1)
            errExit("mq_receive");

        pid = fork();                   /* Create child process */
        if (pid == -1) {
            errMsg("fork");
            break;
        }

        if (pid == 0) {                 /* Child handles request */
            serveRequest(&req);
            _exit(EXIT_SUCCESS);
        }

        /* Parent loops to receive next client request */
    }
    exit(EXIT_SUCCESS);
}
