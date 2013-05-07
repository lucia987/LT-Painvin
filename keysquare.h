#ifndef KEYSQUARE_H_
#define KEYSQUARE_H_

#define SQUARE_SZ	6
#define SQUARE_AREA	36
#define NUM_LETTERS	26
#define ALPHABET	"ADFGVX"

struct keysquare {
	char str[SQUARE_AREA + 1];
	unsigned char line[SQUARE_AREA];
	unsigned char col[SQUARE_AREA];
};

void add_keysquare(char *keysquare, struct keysquare *ks);
void get_keysquare(struct keysquare *ks, char c, char *result);

#endif
