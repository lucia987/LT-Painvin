#include <stdlib.h>
#include <stdio.h>
#ifndef UTIL_H_
#define UTIL_H

#define BUF_SIZE	250
#define CRYPTBUF_SIZE	500

#define DIE(condition, ...)	{\
	if(condition)\
	{\
		fprintf(stderr, "ERROR: ");\
		fprintf(stderr, __VA_ARGS__);\
		fprintf(stderr, "\n");\
		exit(EXIT_FAILURE);\
	}}
#define DIE_ERRNO(condition, message)	{\
	if(condition)\
	{\
		perror("ERROR: " message);\
		exit(EXIT_FAILURE);\
	}}
#define DEBUG(...)	{\
	printf("DEBUG: ");\
	printf(__VA_ARGS__);\
	printf("\n");\
	fflush(stdout);\
	}

#endif
