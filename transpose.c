#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "transpose.h"

void check_transpose_key(char *tkey)
{
	int i;
	
	for (i = 0; i < strlen(tkey); i++)
	{
		tkey[i] = tolower(tkey[i]);
		DIE((tkey[i] < 'a' || tkey[i] > 'z'), "Transposition key must be all letters");
	}
}

void init_transpose_key(struct transpose_key *tk, char *key, int size)
{
	DEBUG("init_transpose_key(key=%s, size=%d)", key, size);
	tk->size = size;
	tk->elem = (struct transpose_key_elem *)malloc(size * sizeof *(tk->elem));
	int i;
	for (i = 0; i < size; i++) {
		tk->elem[i].c = key[i];
		tk->elem[i].p = i;
	}
	quicksort(tk, 0, tk->size-1);
}

char* print_transpose_key(struct transpose_key tk)
{
	int i;
	char *str = (char *)calloc(tk.size+1, sizeof(*str));
	for (i = 0; i < tk.size; i++)
		str[i] = tk.elem[i].c;
	return str;
}

void quicksort(struct transpose_key *tk, int left, int right)
{
	//DEBUG("quicksort(key=%s, left=%d, right=%d", print_transpose_key(*tk), left, right);
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
		while (tk->elem[left].c < pivot.c)
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

char* transpose_plain(struct transpose_key key, char *plain, int size)
{
	//DEBUG("transpose_plain(plain=%s size=%d)", plain, size);
	int n_columns = key.size;
	int n_lines = size / key.size;
	int n_fuller_columns = size % key.size;
	int lin, col;
	char *cipher = (char *)malloc((size+1) * sizeof (*cipher));
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
	return cipher;
}

char* transpose_cipher(struct transpose_key key, char *cipher, int size)
{
	int n_columns = key.size;
	int n_lines = size / key.size;
	int n_fuller_columns = size % key.size;
	int lin, col;
	char *plain = (char *)malloc((size+1) * sizeof (*cipher));
	char *p = cipher;
	for (col = 0; col < n_columns; col ++)
	{
		int actual_col = key.elem[col].p;
		for (lin = 0; lin < n_lines; lin ++) {
			plain[lin * n_columns + actual_col] = *p;
			p ++;	
		}
		if (actual_col < n_fuller_columns) {
			plain[n_lines * n_columns + actual_col] = *p;
			p ++;
		}
	}
	plain[size] = '\0';
	return plain;
}
