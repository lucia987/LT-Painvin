#include <string.h>
#include "keysquare.h"

void add_keysquare(char *keysquare, struct keysquare *ks)
{
	char *p = keysquare;
	int count = 0, index;

	memcpy(ks->str, keysquare, SQUARE_AREA);
	ks->str[SQUARE_AREA] = '\0';
	while (*p != '\0')
	{
		if(*p < 'a')
			index = NUM_LETTERS + *p - '0';
		else 
			index = *p - 'a';
		ks->line[index] = count / SQUARE_SZ;
		ks->col[index] = count % SQUARE_SZ;
		p ++;
		count ++;
	}
}

void get_keysquare(struct keysquare *ks, char c, char *result)
{
	int index;

	if (c < 'a')
		index = NUM_LETTERS + c - '0';
	else
		index = c - 'a';
	result[0] = ALPHABET[ks->line[index]];
	result[1] = ALPHABET[ks->col[index]];
}
