all: server client

server: message_queues_server.c tlpi_hdr.h get_num.h error_functions.h message_queues.h
	gcc -o server message_queues_server.c get_num.c error_functions.c

client: message_queues_client.c tlpi_hdr.h get_num.h error_functions.h message_queues.h
	gcc -o client message_queues_client.c get_num.c error_functions.c

clean:
	rm -f server client