#ifndef SUBSTITUTE_H_
#define SUBSTITUTE_H_

#define N_CODE		6
#define N_CODE_SQRD	36
#define N_ALPHABET	26

struct substitute_key {
	char str[N_CODE_SQRD + 1];
	unsigned char line[N_CODE_SQRD];
	unsigned char col[N_CODE_SQRD];
};

void check_substitute_key(char *skey);
void init_substitute_key(char *keysquare, struct substitute_key *ks);
char *substitute_plain(struct substitute_key ks, char *plain, int size);
char *substitute_cipher(struct substitute_key ks, char *cipher, int size);

#endif
