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

void init_transpose_key(struct transpose_key *tk, char *key, int size);
void fprint_transpose_key(FILE *fd, struct transpose_key tk);
void quicksort(struct transpose_key *tk, int left, int right);
char* transpose_plain(char *plain, int size, struct transpose_key key);
char* transpose_cipher(char *cipher, int size, struct transpose_key key);

#endif
