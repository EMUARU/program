/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2020.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 44-7 */

#include <signal.h>
#include "message_queues.h"

int main(int argc, char *argv[])
{
    int seqNum = 0;
    int serverId;
    struct request req;
    struct response resp;
    pid_t pid;
    ssize_t msgLen;

    umask(0);

    serverId = msgget(SERVER_KEY, IPC_CREAT |
                            S_IRUSR | S_IWUSR | S_IWGRP);
    if (serverId == -1)
        errExit("msgget");


    for (;;) {                          /* Read requests and send responses */
        if ((msgLen = msgrcv(serverId, &req, sizeof(req), 1, 0)) == -1)
            errExit("msgrcv");

        char pidBuf[10];
        char seqLenBuf[10];
        int pidLength = snprintf(pidBuf, sizeof(pidBuf), "%d", req.pid);
        int seqLenLength = snprintf(seqLenBuf, sizeof(seqLenBuf), "%d", req.seqLen);

        char temp[] = "Received messages from client pid = ";
        write(1, temp, sizeof(temp));
        write(1, pidBuf, sizeof(pidLength));
        char temp1[] = ", seqLen = ";
        write(1, temp1, sizeof(temp1));
        write(1, seqLenBuf, sizeof(seqLenLength));
        write(1, "\n", 1);

        resp.mtype = req.pid;
        resp.seqNum = seqNum;
        msgsnd(req.clientId, &resp, sizeof(resp), 0);

        seqNum += req.seqLen;
    }

    if (msgctl(serverId, IPC_RMID, NULL) == -1)
        errExit("msgctl");
}
