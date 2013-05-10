#include <stdlib.h>
#include <stdio.h>
#include "compress.h"

char cipher_chars_by_compression[] =	{ 'X', '.', 'D', '.', 'F', 
					  'G', '.', '.', '.', 'V', 'A'};

void fprintf_compress_text(FILE *fd, struct compress_text comp)
{
	int i;

	for (i=0; i < comp.size; i++) {
		fprintf (fd, "%x | %x |", comp.text[i]&0x0f, comp.text[i]>>4);
	}
}

unsigned char compress_cript_char(char c)
{
	return (c % 11 + 1);
}

char de_compress_cript_char(unsigned char c)
{
	return cipher_chars_by_compression[c];
}

struct compress_text *compress_cripted_text(char *cript_text, int size)
{
	int i;
	struct compress_text *ct = (struct compress_text *)malloc(sizeof *ct);
	ct->size = size / 2 + size % 2 + 1;
	ct->text = (char *)malloc(size * sizeof *(ct->text));
	
	for (i = 0; i < size; i++)
	{
		if (i % 2)
			ct->text[i / 2] |= compress_cript_char(cript_text[i]) << 4;
		else
			ct->text[i / 2] = compress_cript_char(cript_text[i]);
	}

	return ct;
}

char *de_compress_cripted_text(unsigned char *compress_text, int size)
{
	int i, index;
	char *cript_text = (char *)calloc((size * 2 + 1), sizeof *cript_text);

	for (i = 0; i < size; i++)
	{
		index = (compress_text[i] & 0x0f) - 1;
		if (index < 0)
			break;

		cript_text[i * 2] = cipher_chars_by_compression[index];
		cript_text[i * 2 + 1] = cipher_chars_by_compression[(compress_text[i] >> 4) - 1];
	}
	cript_text[size * 2] = '\0';

	return cript_text;
}
