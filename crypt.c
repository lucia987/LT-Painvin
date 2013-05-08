#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "substitute.h"
#include "transpose.h"
#include "crypt.h"

char check_key(char *key)
{
	return 0;	
}

char check_keysquare(char *keysquare)
{
	return 0;
}

char* substitute(char *keysquare, char *plain_text)
{
	struct substitute_key sk;
	char *subst_text;
	
	init_substitute_key(keysquare, &sk);	
	subst_text = substitute_plain(&sk, plain_text, strlen(plain_text));

	return subst_text;
}

char* de_substitute(char *keysquare, char *subst_text)
{
	struct substitute_key sk;
	char *plain_text;
	
	init_substitute_key(keysquare, &sk);	
	plain_text = substitute_cipher(&sk, subst_text, strlen(subst_text));

	return plain_text;
}

char* transpose(char *key, char *subst_text)
{
	struct transpose_key tk;
	char *cipher_text;

	init_transpose_key(&tk, key, strlen(key));
	cipher_text = transpose_plain(subst_text, strlen(subst_text), tk);	
	return cipher_text;
}

char* de_transpose(char *key, char *cipher_text)
{
	struct transpose_key tk;
	char *subst_text;

	init_transpose_key(&tk, key, strlen(key));
	subst_text = transpose_cipher(cipher_text, strlen(cipher_text), tk);	
	return cipher_text;
}

char* crypt(char *key, char *keysquare, char *plain_text)
{
	printf("subst %s\n", substitute(keysquare, plain_text));

	return transpose(key, substitute(keysquare, plain_text));
	//return transpose(key, plain_text);
}

char* de_crypt(char *key, char *keysquare, char *cipher_text)
{
//	return de_substitute(keysquare, de_transpose(key, cipher_text));
	return de_transpose(key, cipher_text);
}

