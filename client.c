#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "util.h"
#include "cli_args.h"
#include "socket.h"
#include "compress.h"
#include "substitute.h"
#include "transpose.h"

void send_file(int sockfd, char *filename, struct substitute_key sk, struct transpose_key tk)
{	
	char buffer[BUF_SIZE+1];
	FILE *fd;
	int ret;

	fd = fopen(filename, "r");
	DIE_ERRNO(fd == NULL, "fopen");

	while (1)
	{
		
		/* Reserve memory for cleartext message */
		memset(buffer, 0, BUF_SIZE+1);

		/* Read file chunk in buffer */
		int count = fread(buffer, sizeof(*buffer), BUF_SIZE, fd);
		DIE_ERRNO(count < 0, "fread");

		if (count == 0)
		{
			break;
		}

		/* Crypt cleartext message */
		char *substbuf = substitute_plain(sk, buffer, strlen(buffer));
		char *transbuf = transpose_plain(tk, substbuf, strlen(substbuf));

		/* Compress cryped text */
		struct compress_text *compressbuf =
			compress_crypted_text(transbuf, strlen(transbuf));

		/* Send compressed crypted message */
		ret = send(sockfd, compressbuf->text, compressbuf->size, 0);
		DIE_ERRNO(ret < 0, "Cannot write to socket");
		//DEBUG("Sent message %s", buffer);
	}
	fclose(fd);
	DEBUG("Sent file %s as ADFGVX message.", filename);
}

int main(int argc, char **argv)
{
	int sockfd, ret;
	struct sockaddr_in server_addr;
	struct hostent *server;
	struct cliargs cliargs;
	struct substitute_key sk;
	struct transpose_key tk;

	cliargs = parse_cli_args(argc, argv);
	DEBUG("Parsed CLI args.");

	/* Initialize ADFGVX key structures */
	init_substitute_key(cliargs.skey, &sk);
	init_transpose_key(&tk, cliargs.tkey, strlen(cliargs.tkey));

	/* Create TCP socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE_ERRNO(sockfd < 0, "socket");
	DEBUG("Created socket.");

	/* Get server hostent struct */
	server = gethostbyname(cliargs.hostname);
	DIE_ERRNO(server == NULL, "No such host");

	/* Initialize address structure */
	memset((char *) &server_addr, 0, sizeof server_addr);
	server_addr.sin_family = AF_INET;
	memcpy((char *)&server_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
	server_addr.sin_port = htons(cliargs.portno);
	
	/* Connect to server socket */
	ret = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	DIE_ERRNO(ret < 0, "Connect to server");

	send_file(sockfd, cliargs.file, sk, tk);

	/* Close socket */	
	close(sockfd);
	DEBUG("Closed socket.");

	return 0;
}
