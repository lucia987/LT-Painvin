#include <stdlib.h>
#ifndef UTIL_H_
#define UTIL_H

#define BUF_SIZE	256
#define DIE(condition, message)	{if(condition)				\
				{					\
					fprintf(stderr, "ERROR: " message"\n");	\
					exit(EXIT_FAILURE);			\
				}}
#define ERROR_EXIT(condition, message)	{if(condition)				\
				{					\
					perror("ERROR: " message);	\
					exit(EXIT_FAILURE);			\
				}}

#endif
