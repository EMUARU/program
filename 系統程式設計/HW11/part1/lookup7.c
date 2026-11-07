/*
 * lookup7 : does no looking up locally, but instead asks
 * a server for the answer. Communication is by Unix TCP Sockets
 * The name of the socket is passed as resource.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "dict.h"

int lookup(Dictrec * sought, const char * resource) {
	static int sockfd;
	static struct sockaddr_un server;
	static int first_time = 1;
	int n;

	if (first_time) {     /* connect to socket ; resource is socket name */
		first_time = 0;

		/* Set up destination address.
		 * Fill in code. */
		server.sun_family = AF_UNIX;
		strcpy(server.sun_path,resource);

		/* Allocate socket. */
		if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
			DIE("sockfd");

		/* Connect to the server.
		 * Fill in code. */
		if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) == -1)
			DIE("connect");		
	}

	/* write query on socket ; await reply
	 * Fill in code. */
	if ((n = write(sockfd, sought->word, sizeof(sought->word))) < 0)
    	DIE("write");

    if ((n = read(sockfd, sought->text, sizeof(sought->text))) < 0)
    	DIE("read");

	if (strcmp(sought->text,"Word not found") != 0) {
		return FOUND;
	}

	return NOTFOUND;
}
