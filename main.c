#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transpose.h"
#include "crypt.h"

int main(int argc, char **argv)
{
	char keysquare[] = "ph0qg64mea1yl2nofdxkr3cvs5zw7bj9uti8";
	char key[] = "german";
	char text[] = "undeteducisambataviitoare";


	struct transpose_key tk;
	char *cipher_text;
	char *subst_text;

	init_transpose_key(&tk, key, strlen(key));
	cipher_text = transpose_plain(text, strlen(text), tk);	
	init_transpose_key(&tk, key, strlen(key));
	subst_text = transpose_cipher(cipher_text, strlen(cipher_text), tk);	

	printf("cipher %s\n", cipher_text);
	printf("text %s\n", subst_text);

	char *cipher = crypt(key, keysquare, text);
	printf("cipher %s\n", cipher);
	char *plain = de_crypt(key, keysquare, cipher);
	printf("text %s\n", plain);
}

