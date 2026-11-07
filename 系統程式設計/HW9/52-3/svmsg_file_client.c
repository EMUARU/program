/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 46-9 */

#include "svmsg_file.h"

static int clientId;

static void
removeQueue(void)
{
    mq_unlink("/client_queue");
}

int
main(int argc, char *argv[])
{
    struct requestMsg req;
    struct responseMsg resp;
    int numMsgs;
    ssize_t msgLen, totBytes;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s pathname\n", argv[0]);

    if (strlen(argv[1]) > sizeof(req.pathname) - 1)
        cmdLineErr("pathname too long (max: %ld bytes)\n",
                (long) sizeof(req.pathname) - 1);

    /* Get server's queue identifier; create queue for response */

    mqd_t mq_client_queue;
    mqd_t mq_server_queue;
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(struct responseMsg);
    attr.mq_curmsgs = 0;

    mq_client_queue  = mq_open("/client_queue", O_CREAT | O_RDWR, 0644, &attr);
    if (mq_client_queue == (mqd_t)-1)
        errExit("mq_open");

    mq_server_queue = mq_open("/server_queue", O_WRONLY);
    if (mq_server_queue == (mqd_t)-1)
        errExit("mq_open 1");

    if (atexit(removeQueue) != 0)
        errExit("atexit");

    /* Send message asking for file named in argv[1] */

    req.mtype = 1;                      /* Any type will do */
    strncpy(req.pathname, argv[1], sizeof(req.pathname) - 1);
    req.pathname[sizeof(req.pathname) - 1] = '\0';
                                        /* Ensure string is terminated */

    if (mq_send(mq_server_queue, (char *)&req, sizeof(struct requestMsg), 0) == -1)
        errExit("mq_send");

    /* Get first response, which may be failure notification */

    if ((msgLen = mq_receive(mq_client_queue, (char *)&resp, sizeof(struct responseMsg) * 10, NULL)) == -1)
        errExit("mq_receive");

    /* File was opened successfully by server; process messages
       (including the one already received) containing file data */

    if (resp.mtype != RESP_MT_DATA)
    {
        printf("Received 0 bytes (1 messages)\n");
        exit(0);
    }

    totBytes = msgLen - sizeof(int);                  /* Count first message */
    for (numMsgs = 1; resp.mtype == RESP_MT_DATA; numMsgs++) {
        if ((msgLen = mq_receive(mq_client_queue, (char *)&resp, sizeof(struct responseMsg), NULL)) == -1)
            errExit("mq_receive");

        if (resp.mtype != RESP_MT_DATA)
            break;

        totBytes += (msgLen - sizeof(int));
    }

    printf("Received %ld bytes (%d messages)\n", (long) totBytes, numMsgs);

    exit(EXIT_SUCCESS);
}
