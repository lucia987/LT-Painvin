#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "cli_args.h"
#include "substitute.h"
#include "transpose.h"

void print_usage(int status)
{
	if (status)
		fprintf(stderr, "Try %s --help for more information.\n",
			program_name);
	else 
	{
		printf("Usage: %s\n%s", program_name, usage);
	}
}

void check_port(char *cli_port)
{
	portno = atoi(cli_port);
	DIE(portno < 0 || portno >= 65536, "Port must be in port range 1-65535");
}

void check_tkey(char *cli_tkey)
{
	check_transpose_key(cli_tkey);

	tkey = (char *)calloc(TKEY_LEN + 1, sizeof *tkey);
	memcpy(tkey, cli_tkey, TKEY_LEN);
}

void check_skey(char *cli_skey)
{
	check_substitute_key(cli_skey);

	skey = (char *)calloc(SKEY_LEN + 1, sizeof *skey);
	memcpy(skey, cli_skey, SKEY_LEN);
}

void check_file(char *cli_file)
{
	file = (char *)calloc(FILE_LEN + 1, sizeof *file);
	memcpy(file, cli_file, FILE_LEN);
}

void check_server(char *cli_server)
{
	server = (char *)calloc(SERVER_LEN + 1, sizeof *server);
	memcpy(server, cli_server, SERVER_LEN);
}

int check_mandatory_optargs()
{
#ifdef IS_CLIENT
	DIE(server == NULL, "Add --server=NAME to define server hostname");
#endif
	DIE(portno == -1, "Add --port==PORTNO to define server port");

	DIE(tkey == NULL, "Add --tkey==TRANSPOSE-KEY to define ADFGVX transposition key");

	DIE(skey == NULL, "Add --skey==SUBSTITUE-KEY to define ADFGVX substitution keysquare");

#ifdef IS_CLIENT
	DIE(file == NULL, "Add --file==FILE to define input message file");
#else
	DIE(file == NULL, "Add --file==FILE to define output message file");
#endif
}

void parse_cli_arguments(int argc, char **argv)
{
	int opt = 0, longindex;

	program_name = argv[0];

	while ((opt = getopt_long(argc, argv, OPTSTR, longopts, &longindex)) != -1)
	{
		switch (opt)
		{
			case 0:
				break;
			case 'n':
				check_server(optarg);
				break;
			case_GETOPT_PORT_CHAR;

			case_GETOPT_TKEY_CHAR;

			case_GETOPT_SKEY_CHAR;

			case_GETOPT_FILE_CHAR;

			case_GETOPT_HELP_CHAR;

			default:
				print_usage(EXIT_FAILURE);
		}
	}
	check_mandatory_optargs();
}

