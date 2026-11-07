all: udp_server udp_client

udp_server: dict.h lookup5.c udp_server.c
	gcc -o udp_server lookup5.c udp_server.c

udp_client: dict.h lookup9.c main.c
	gcc -o udp_client lookup9.c main.c

clean:
	rm -f udp_server udp_client