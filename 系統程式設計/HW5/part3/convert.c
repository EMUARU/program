/*
 * convert.c : take a file in the form 
 *  word1
 *  multiline definition of word1
 *  stretching over several lines, 
 * followed by a blank line
 * word2....etc
 * convert into a file of fixed-length records
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "dict.h"
#define BIGLINE 512

int main(int argc, char **argv) {
	FILE *in;
	FILE *out;        /* defaults */
	char line[BIGLINE];
	static Dictrec dr, blank;
	
	/* If args are supplied, argv[1] is for input, argv[2] for output */
	if (argc==3) {
		if ((in =fopen(argv[1],"r")) == NULL){DIE(argv[1]);}
		if ((out =fopen(argv[2],"w")) == NULL){DIE(argv[2]);}	
	}
	else{
		printf("Usage: convert [input file] [output file].\n");
		return -1;
	}

	/* Main reading loop : read word first, then definition into dr */

	/* Loop through the whole file. */
	while (fgets(dr.word, sizeof(dr.word), in) != NULL) {
		
		/* Create and fill in a new blank record.
		 * First get a word and put it in the word field, then get the definition
		 * and put it in the text field at the right offset.  Pad the unused chars
		 * in both fields with nulls.
		 */

		/* Read word and put in record.  Truncate at the end of the "word" field.
		 *
		 * Fill in code. */
		memset(dr.text, '\0', sizeof(dr.text));
		int numWord;
		numWord = strlen(dr.word) - 1;
		dr.word[numWord] = '\0';

		int numBlankWord = 32 - numWord;

		/* Read definition, line by line, and put in record.
		 *
		 * Fill in code. */
		char buf[480];
		int numRead;
		//int numBlank = 512 - numWord;
		int numBlankText = 480;
		while (fgets(buf, sizeof(buf), in) != NULL)
		{
			if (strcmp(buf, "\n") == 0)
				break;
			numRead = strlen(buf) - 1;
			buf[numRead] = '\0';
			strcat(dr.text, buf);
			numBlankText -= numRead;
		}

		/* Write record out to file.
		 *
		 * Fill in code. */
		fprintf(out, "%s", dr.word);
		for (int i = 0; i < numBlankWord; i++)
			fputc('\0', out);

		fprintf(out, "%s", dr.text);
		for (int i = 0; i < numBlankText; i++)
			fputc('\0', out);
	}

	fclose(in);
	fclose(out);
	return 0;
}
