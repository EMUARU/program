/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 44-8 */

#include "message_queues.h"

static int clientId;

static void
removeQueue(void)
{
    if (msgctl(clientId, IPC_RMID, NULL) == -1)
        errExit("msgctl");
}

int
main(int argc, char *argv[])
{
    struct request req;
    struct response resp;
    int serverId;
    ssize_t msgLen;
    int pid;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [seq-len]\n", argv[0]);

    pid = getpid();

    umask(0);
    req.pid = pid;
    req.seqLen = (argc > 1) ? getInt(argv[1], GN_GT_0, "seq-len") : 1;

    serverId = msgget(SERVER_KEY, S_IWUSR);
    if (serverId == -1)
        errExit("msgget - server message queue");

    clientId = msgget(IPC_PRIVATE, S_IRUSR | S_IWUSR | S_IWGRP);
    if (clientId == -1)
        errExit("msgget - client message queue");

    req.mtype = 1;
    req.clientId = clientId;

    if (msgsnd(serverId, &req, sizeof(req), 0) == -1)
        errExit("msgsnd");

    msgLen = msgrcv(clientId, &resp, sizeof(resp), pid, 0);
    if (msgLen == -1)
        errExit("msgrcv");

    printf("%d\n", resp.seqNum);
    removeQueue();
    exit(EXIT_SUCCESS);
}
