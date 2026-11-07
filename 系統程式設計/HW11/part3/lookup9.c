/*
 * lookup9 : does no looking up locally, but instead asks
 * a server for the answer. Communication is by Internet UDP Sockets
 * The name of the server is passed as resource. PORT is defined in dict.h
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include "dict.h"

int lookup(Dictrec * sought, const char * resource) {
	static int sockfd;
	static struct sockaddr_in server;
	struct hostent *host;
	static int first_time = 1;

	if (first_time) {  /* Set up server address & create local UDP socket */
		first_time = 0;

		/* Set up destination address.
		 * Fill in code. */
		memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        if ((host = gethostbyname(resource)) == NULL)
        	DIE("gethostbyname");
        memcpy((char *)&server.sin_addr.s_addr, (char *)host->h_addr, host->h_length);
        server.sin_port = htons(PORT);

		/* Allocate a socket.
		 * Fill in code. */
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        	DIE("socket");
	}

	/* Send a datagram & await reply
	 * Fill in code. */
	socklen_t serverlen = sizeof(server);

	if (sendto(sockfd, sought->word, strlen(sought->word)+1, 0, (struct sockaddr *)&server, serverlen) < 0)
		DIE("sendto");

	if (recvfrom(sockfd, sought->text, sizeof(sought->text), 0, (struct sockaddr *)&server, &serverlen) < 0)
		DIE("recvfrom");

	if (strcmp(sought->text,"Word not found") != 0) {
		return FOUND;
	}

	return NOTFOUND;
}
