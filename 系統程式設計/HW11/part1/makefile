all: usock_server usock_client

usock_server: dict.h lookup5.c usock_server.c
	gcc -o usock_server lookup5.c usock_server.c

usock_client: dict.h lookup7.c main.c
	gcc -o usock_client lookup7.c main.c

clean:
	rm -f usock_server usock_client