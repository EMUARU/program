all: isock_server isock_client

isock_server: dict.h lookup5.c isock_server.c
	gcc -o isock_server lookup5.c isock_server.c

isock_client: dict.h lookup8.c main.c
	gcc -o isock_client lookup8.c main.c

clean:
	rm -f isock_server isock_client