#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypt.h"

int main(int argc, char **argv)
{
	char keysquare[] = "ph0qg64mea1yl2nofdxkr3cvs5zw7bj9uti8";
	char key[] = "german";
	char text[] = "undeteducisambataviitoare12345";

	printf("%s\n", de_crypt(key, keysquare, crypt(key, keysquare, text)));	
	return 0;
}

