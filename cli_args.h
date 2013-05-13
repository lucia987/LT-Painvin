#include <getopt.h>

#ifndef CLI_ARGS_H
#define CLI_ARGS_H

#define OPTSTR	"h"

#define TKEY_LEN	255
#define SKEY_LEN	36
#define FILE_LEN	255
#define SERVER_LEN	255

#define IS_CLIENT	1
#ifdef IS_CLIENT
char *server;
#endif
int portno = -1;
char *tkey = NULL, *skey = NULL, *file = NULL;
char *program_name;

#define GETOPT_PORT_OPTION_DECL	{"port", required_argument, NULL, 'p'}
#define GETOPT_TKEY_OPTION_DECL	{"tkey", required_argument, NULL, 't'}
#define GETOPT_SKEY_OPTION_DECL	{"skey", required_argument, NULL, 's'}
#define GETOPT_FILE_OPTION_DECL	{"file", required_argument, NULL, 'f'}
#define GETOPT_HELP_OPTION_DECL	{"help", no_argument, NULL, 'h'}

#define case_GETOPT_PORT_CHAR	case 'p': 		\
					check_port(optarg);	\
					break;		
#define case_GETOPT_TKEY_CHAR	case 't': 		\
					check_tkey(optarg);	\
					break;		
#define case_GETOPT_SKEY_CHAR	case 's': 		\
					check_skey(optarg);	\
					break;
#define case_GETOPT_FILE_CHAR	case 'f':		\
					check_file(optarg);	\
					break;
#define case_GETOPT_HELP_CHAR	case 'h':		\
					print_usage(0);	\
					break;
char *usage = 
/*
#ifdef IS_CLIENT
	"-n, --server=SERVER_HOSTNAME\n"	\
#endif
*/
	"\t--port=SERVER_PORT\n"	\
	"\t--tkey=TRANSPOSE_KEY\n"	\
	"\t--skey=SUBSTITUTE_KEY\n"	\
	"\t--file=INPUT_FILE\n"	\
	"\t-h, --help\n";

const struct option longopts[] =
{
#ifdef IS_CLIENT
	{"server", required_argument, NULL, 'n'},
#endif
	GETOPT_PORT_OPTION_DECL,
	GETOPT_TKEY_OPTION_DECL,
	GETOPT_SKEY_OPTION_DECL,
	GETOPT_FILE_OPTION_DECL,
	GETOPT_HELP_OPTION_DECL,
	{NULL, 0, NULL, 0}
};

void check_port(char *cli_port);
void check_tkey(char *cli_tkey);
void check_skey(char *cli_skey);
void check_file(char *cli_file);
void check_server(char *cli_server);
int check_mandatory_optargs()
void parse_cli_arguments(int argc, char **argv)
#endif
