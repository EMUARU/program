all: server client

server: svmsg_file_server.c tlpi_hdr.h get_num.h error_functions.h svmsg_file.h
	gcc -o server svmsg_file_server.c get_num.c error_functions.c

client: svmsg_file_client.c tlpi_hdr.h get_num.h error_functions.h svmsg_file.h
	gcc -o client svmsg_file_client.c get_num.c error_functions.c

clean:
	rm -f server client