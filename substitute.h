#ifndef SUBSTITUTE_H_
#define SUBSTITUTE_H_

#define N_CODE		6
#define N_CODE_SQRD	36
#define N_ALPHABET	26
#define CODE		"ADFGVX"

struct substitute_key {
	char str[N_CODE_SQRD + 1];
	unsigned char line[N_CODE_SQRD];
	unsigned char col[N_CODE_SQRD];
};

void init_keysquare(char *keysquare, struct substitute_key *ks);
void substitute_plain(struct substitute_key *ks, char plain, char *cipher);
char substitute_cipher(struct substitute_key *ks, char cipher[2]);

#endif
