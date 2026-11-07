all: convert file_lookup

convert: convert.c dict.h
	gcc -o convert convert.c

file_lookup: lookup1.c main.c dict.h
	gcc -o file_lookup lookup1.c main.c