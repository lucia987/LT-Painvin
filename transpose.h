#ifndef TRANSPOSE_H_
#define TRANSPOSE_H_

struct transpose_key_elem {
	char c;
	unsigned char p;
};

struct transpose_key {
	int size;
	struct transpose_key_elem *elem;
};

struct reverse_key {
	int size;
	unsigned char *p;
};

void check_transpose_key(char *tkey);
void init_transpose_key(struct transpose_key *tk, char *key, int size);
char* print_transpose_key(struct transpose_key tk);
void quicksort(struct transpose_key *tk, int left, int right);
char* transpose_plain(struct transpose_key key, char *plain, int size);
char* transpose_cipher(struct transpose_key key, char *cipher, int size);

#endif
