#include <string.h>
#include <stdlib.h>
#include "substitute.h"

void init_substitute_key(char *keysquare, struct substitute_key *ks)
{
	char *p = keysquare;
	int count = 0, index;

	memcpy(ks->str, keysquare, N_CODE_SQRD);
	ks->str[N_CODE_SQRD] = '\0';
	while (*p != '\0')
	{
		if(*p < 'a')
			index = N_ALPHABET + *p - '0';
		else 
			index = *p - 'a';
		ks->line[index] = count / N_CODE;
		ks->col[index] = count % N_CODE;
		p ++;
		count ++;
	}
}

void substitute_plain_elem(struct substitute_key *ks, char plain, char *cipher)
{
	int index;

	if (plain < 'a')
		index = N_ALPHABET + plain - '0';
	else
		index = plain - 'a';
	cipher[0] = CODE[ks->line[index]];
	cipher[1] = CODE[ks->col[index]];
}

char *substitute_plain(struct substitute_key *ks, char *plain, int size)
{
	int i;
	char *cipher = (char *)malloc(2 * size * sizeof(*cipher));

	for (i = 0; i < size; i ++)
	{
		substitute_plain_elem(ks, plain[i], cipher + 2*i);
	}
	return cipher;
}

char substitute_cipher_elem(struct substitute_key *ks, char cipher[2])
{
	int line, col;
	int i;
	
	for (i = 0; i < N_CODE; i ++)
		if (cipher[0] == CODE[i]) {
			line = i;
			break;
		}
	for (i = 0; i < N_CODE; i ++)
		if (cipher[1] == CODE[i]) {
			col = i;
			break;
		}
	return ks->str[line * N_CODE + col];
}

char *substitute_cipher(struct substitute_key *ks, char *cipher, int size)
{
	int i;
	char *plain = (char *)malloc(size * sizeof(*plain));

	for (i = 0; i < size/2; i++)
	{
		plain[i] = substitute_cipher_elem(ks, cipher + 2*i);
	}
	return plain;
}
