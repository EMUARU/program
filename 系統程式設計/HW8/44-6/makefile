all: server client client_without_open_fifo

server: fifo_seqnum_server.c tlpi_hdr.h get_num.h error_functions.h
	gcc -o server fifo_seqnum_server.c fifo_seqnum.h get_num.c error_functions.c

client: fifo_seqnum_client.c tlpi_hdr.h get_num.h error_functions.h
	gcc -o client fifo_seqnum_client.c fifo_seqnum.h get_num.c error_functions.c

client_without_open_fifo: client_without_open_fifo.c tlpi_hdr.h get_num.h error_functions.h
	gcc -o client_without_open_fifo client_without_open_fifo.c fifo_seqnum.h get_num.c error_functions.c

clean:
	rm -f server client client_without_open_fifo