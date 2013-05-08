#include <stdio.h>
#include <stdlib.h>
#include "transpose.h"

void init_transpose_key(struct transpose_key *tk, char *key, int size)
{
	tk->size = size;
	tk->elem = (struct transpose_key_elem *)malloc(size * sizeof *(tk->elem));
	int i;
	for (i = 0; i < size; i++) {
		tk->elem[i].c = key[i];
		tk->elem[i].p = i;
	}
}

struct reverse_key* reverse_tranpose_key(struct transpose_key tk, struct reverse_key *rk)
{
	int i;
	rk->p = (unsigned char *)malloc(tk.size *sizeof *(rk->p));
	for (i = 0; i < tk.size; i++)
	{
		rk->p[tk.elem[i].p] = i;
	}
}

void fprint_transpose_key(FILE *fd, struct transpose_key tk)
{
	int i;
	for (i = 0; i < tk.size; i++)
	{
		fprintf(fd, "%d %c\n", tk.elem[i].p, tk.elem[i].c);
	} 
}

void quicksort(struct transpose_key *tk, int left, int right)
{
	if (left >= right)
		return;
	if (right - left == 1 && tk->elem[left].c > tk->elem[right].c) {
		struct transpose_key_elem aux = tk->elem[left];
		tk->elem[left] = tk->elem[right];
		tk->elem[right] = aux; 
		return;
	}

	struct transpose_key_elem pivot = tk->elem[left];
	int old_left = left ++, old_right = right;
	while (left < right) {
		while (tk->elem[left].c <= pivot.c)
			left ++;
		while (tk->elem[right].c > pivot.c)
	 		right --;
		if (left < right) {
			struct transpose_key_elem aux = tk->elem[left];
			tk->elem[left] = tk->elem[right];
			tk->elem[right] = aux; 
			left ++; right --;
		}
	}
	tk->elem[old_left] = tk->elem[left-1];
	tk->elem[left-1] = pivot;

	quicksort(tk, old_left, left - 2);
	quicksort(tk, left, old_right); 
}

void transpose_plain(char *plain, char *cipher, int size, struct transpose_key key)
{
	int n_columns = key.size;
	int n_lines = size / key.size;
	int n_fuller_columns = size % key.size;
	int lin, col;
	char *p = cipher;
	for (col = 0; col < n_columns; col ++)
	{
		int actual_col = key.elem[col].p;
		for (lin = 0; lin < n_lines; lin ++) {
			*p = plain[lin * n_columns + actual_col];
			p ++;	
		}
		if (actual_col < n_fuller_columns) {
			*p = plain[n_lines * n_columns + actual_col];
			p ++;
		}
	}
	*p = '\0';
}

void transpose_cipher(char *cipher, char *plain, int size, struct reverse_key key)
{
	int n_columns = key.size;
	int n_lines = size / key.size;
	int n_fuller_columns = size % key.size;
	int lin, col;
	char *p = cipher;
	for (col = 0; col < n_columns; col ++)
	{
		int actual_col = key.p[col];
		for (lin = 0; lin < n_lines; lin ++) {
			plain[lin * n_columns + actual_col] = *p;
			p ++;	
		}
		if (actual_col < n_fuller_columns) {
			plain[n_lines * n_columns + actual_col] = *p;
			p ++;
		}
	}
}
