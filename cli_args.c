#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "cli_args.h"
#include "substitute.h"
#include "transpose.h"

char *usage =
	"\t--port=SERVER_PORT\n"	\
	"\t--tkey=TRANSPOSE_KEY\n"	\
	"\t--skey=SUBSTITUTE_KEY\n"	\
	"\t-h, --help\n";


void print_usage(int status)
{
	if (status)
		fprintf(stderr, "Try %s --help for more information.\n",
			program_name);
	else 
	{
#ifdef IS_CLIENT
		printf("Usage: %s\n\t--server=SERVER-HOSTNAME\n\t--file=INPUT_FILE\n%s",
			program_name, usage);
	
#else
		printf("Usage: %s\n%s", program_name, usage);
#endif
	}
}

void check_port(struct cliargs *cliargs, char *cli_port)
{
	DEBUG("Checking port.");
	cliargs->portno = atoi(cli_port);
	DIE(cliargs->portno < 0 || cliargs->portno >= 65536, "Port must be in port range 1-65535");
	DEBUG("Port OK.");
}

void check_tkey(struct cliargs *cliargs, char *cli_tkey)
{
	DEBUG("Checking tkey.");
	check_transpose_key(cli_tkey);

	cliargs->tkey = (char *)calloc(TKEY_LEN + 1, sizeof *cliargs->tkey);
	memcpy(cliargs->tkey, cli_tkey, TKEY_LEN);
	DEBUG("Transpose key OK.");
}

void check_skey(struct cliargs *cliargs, char *cli_skey)
{
	DEBUG("Checking skey.");
	check_substitute_key(cli_skey);

	cliargs->skey = (char *)calloc(SKEY_LEN + 1, sizeof *cliargs->skey);
	memcpy(cliargs->skey, cli_skey, SKEY_LEN);
	DEBUG("Substitute key OK.");
}

void check_file(struct cliargs *cliargs, char *cli_file)
{
	DEBUG("Checking file argument.");
	cliargs->file = (char *)calloc(FILE_LEN + 1, sizeof *cliargs->file);
	memcpy(cliargs->file, cli_file, FILE_LEN);
	DEBUG("File argument OK.");
}

#ifdef IS_CLIENT
void check_server(struct cliargs *cliargs, char *cli_server)
{
	DEBUG("Checking server argument.");
	cliargs->hostname = (char *)calloc(SERVER_LEN + 1, sizeof *cliargs->hostname);
	memcpy(cliargs->hostname, cli_server, SERVER_LEN);
	DEBUG("Server argument OK.");
}
#endif

void check_mandatory_optargs(struct cliargs cliargs)
{
#ifdef IS_CLIENT
	DIE(cliargs.hostname == NULL, "Add --server=NAME to define server hostname");
#endif
	DIE(cliargs.portno == -1, "Add --port==PORTNO to define server port");

	DIE(cliargs.tkey == NULL, "Add --tkey==TRANSPOSE-KEY to define ADFGVX transposition key");

	DIE(cliargs.skey == NULL, "Add --skey==SUBSTITUE-KEY to define ADFGVX substitution keysquare");

#ifdef IS_CLIENT
	DIE(cliargs.file == NULL, "Add --file==FILE to define input message file");
#endif
}

struct cliargs parse_cli_args(int argc, char **argv)
{
	int opt = 0, longindex;

	program_name = argv[0];
	struct cliargs cliargs;
	cliargs.portno = -1;
	cliargs.hostname = cliargs.tkey = cliargs.skey = cliargs.file = NULL;

	while ((opt = getopt_long(argc, argv, OPTSTR, longopts, &longindex)) != -1)
	{
		switch (opt)
		{
			case 0:
				break;
#ifdef IS_CLIENT
			case 'n':
				check_server(&cliargs, optarg);
				break;
#endif
			case 'p':
				check_port(&cliargs, optarg);
				break;
			case 't':
				check_tkey(&cliargs, optarg);
				break;
			case 's':
				check_skey(&cliargs, optarg);
				break;
			case 'f':
				check_file(&cliargs, optarg);	\
				break;
			case 'h':
				print_usage(0);	\
				break;
			default:
				print_usage(EXIT_FAILURE);
		}
	}
	check_mandatory_optargs(cliargs);
	return cliargs;
}
/*
int main(int argc, char **argv)
{
	parse_cli_args(argc, argv);
	return 0;
}
*/
