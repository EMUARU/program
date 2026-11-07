/*
 * lookup1 : straight linear search through a local file
 * 	         of fixed length records. The file name is passed
 *	         as resource.
 */
#include <string.h>
#include "dict.h"

int lookup(Dictrec * sought, const char * resource) {
	Dictrec dr;
	static FILE * in;
	static int first_time = 1;

	if (first_time) { 
		first_time = 0;
		/* open up the file
		 *
		 * Fill in code. */
		in = fopen(resource,"r");
		if (in == NULL)
			DIE(resource);
	}

	/* read from top of file, looking for match
	 *
	 * Fill in code. */
	rewind(in);
	while(fread(&dr, sizeof(dr), 1, in) == 1) {
		/* Fill in code. */
		if (strcmp(sought->word, dr.word) == 0)
		{
			strcpy(sought->text, dr.text);
			return FOUND;
		}
	}

	return NOTFOUND;
}
