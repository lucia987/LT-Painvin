#ifndef COMPRESS_H_
#define COMPRESS_H_

struct compress_text
{
	unsigned char *text;
	int size;
};

struct compress_text *compress_cripted_text(char *cript_text, int size);
char *de_compress_cripted_text(unsigned char *compress_text, int size);

#endif
