#ifndef CRYPT_H_
#define CRYPT_H_

char* crypt(char *key, char *keysquare, char *plain_text);
char* de_crypt(char *key, char *keysquare, char *cipher_text);

#endif
