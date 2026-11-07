/*
 * isock_server : listen on an internet socket ; fork ;
 *                child does lookup ; replies down same socket
 * argv[1] is the name of the local datafile
 * PORT is defined in dict.h
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>

#include "dict.h"

int main(int argc, char **argv) {
	static struct sockaddr_in server;
	int sd,cd,n;
	Dictrec tryit;

	if (argc != 2) {
		fprintf(stderr,"Usage : %s <datafile>\n",argv[0]);
		exit(1);
	}

	/* Create the socket.
	 * Fill in code. */
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		DIE("socket");

	/* Initialize address.
	 * Fill in code. */
	memset((char *) &server, 0, sizeof(server));
	server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    int yes = 1;
	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
		DIE("setsockopt");

	/* Name and activate the socket.
	 * Fill in code. */
    if (bind(sd, (struct sockaddr *)&server, sizeof(server)) < 0)
    	DIE("bind");

    if (listen(sd, 128) == -1)
    	DIE("listen");

	/* main loop : accept connection; fork a child to have dialogue */
	for (;;) {

		/* Wait for a connection.
		 * Fill in code. */
		if ((cd = accept(sd, NULL, NULL)) == -1)
    		DIE("accept");

		/* Handle new client in a subprocess. */
		switch (fork()) {
			case -1 : 
				DIE("fork");
			case 0 :
				close (sd);	/* Rendezvous socket is for parent only. */
				/* Get next request.
				 * Fill in code. */
				while ((n = read(cd, tryit.word, sizeof(tryit.word))) > 0) {
					/* Lookup the word , handling the different cases appropriately */
					switch(lookup(&tryit,argv[1]) ) {
						/* Write response back to the client. */
						case FOUND:
							/* Fill in code. */
							write(cd, tryit.text, strlen(tryit.text) + 1);
							break;
						case NOTFOUND:
							/* Fill in code. */
							char buf[] = "Word not found";
							write(cd, buf, sizeof(buf));
							break;
						case UNAVAIL:
							DIE(argv[1]);
					} /* end lookup switch */
				} /* end of client dialog */
				exit(0); /* child does not want to be a parent */

			default :
				close(cd);
				break;
		} /* end fork switch */
	} /* end forever loop */
} /* end main */
