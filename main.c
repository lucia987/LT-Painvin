//#include "adfgvx_crypt.h"
#include <stdio.h>
#include <stdlib.h>
#include "keysquare.h"

int main(int argc, char **argv)
{
	struct keysquare ks;
	char text[3];

	char key[] = "ph0qg64mea1yl2nofdxkr3cvs5zw7bj9uti8";

	add_keysquare(key, &ks);
	
	int i;
	for (i=0; i<36; i++)
	{
		get_keysquare(&ks, key[i], text);
		printf("%2d %s\n", i, text);
	}
	return 0;
}
