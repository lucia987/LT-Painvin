#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "substitute.h"
#include "transpose.h"

int main(int argc, char **argv)
{
	char key[] = "ph0qg64mea1yl2nofdxkr3cvs5zw7bj9uti8";
	char lala[] = "german";
	char text[] = "undeteducisambataviitoare";
	char cipher[30];
	char cipher2[30];

	struct transpose_key tk;
	init_transpose_key(&tk, lala, 6);
	fprint_transpose_key(stdout, tk);
	quicksort(&tk, 0, tk.size-1);
	fprint_transpose_key(stdout, tk);
	
	transpose_plain(text, cipher, strlen(text), tk);
	printf("text cifrat %s\n", cipher);
	memset(cipher2, '0', strlen(text));
	transpose_cipher(cipher, cipher2, strlen(text), );
	printf("text DEScifrat %s\n", cipher2);
}
