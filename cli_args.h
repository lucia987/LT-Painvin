#ifndef CLI_ARGS_H
#define CLI_ARGS_H

#include <getopt.h>

#define OPTSTR		"h"
#define TKEY_LEN	255
#define SKEY_LEN	36
#define FILE_LEN	255
#define SERVER_LEN	255

struct cliargs
{
	char *hostname;
	int portno;
	char *tkey;
	char *skey;
	char *file;
};

static char *program_name;
static const struct option longopts[] =
{
	{"server", required_argument, NULL, 'n'},
	{"port", required_argument, NULL, 'p'},
	{"tkey", required_argument, NULL, 't'},
	{"skey", required_argument, NULL, 's'},
	{"file", required_argument, NULL, 'f'},
	{"help", no_argument, NULL, 'h'},
	{NULL, 0, NULL, 0}
};

struct cliargs parse_cli_args(int argc, char **argv);
#endif
