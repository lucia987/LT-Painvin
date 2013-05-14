#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "util.h"
#include "cli_args.h"
#include "socket.h"
#include "crypt.h"
#include "compress.h"

int main(int argc, char **argv)
{
	int sockfd, n, ret;
	struct sockaddr_in server_addr;
	struct hostent *server;
	char buffer[BUF_SIZE+1];
	struct cliargs cliargs;

	cliargs = parse_cli_args(argc, argv);
	DEBUG("Parsed CLI args.");

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
	
	/* Reserve memory for cleartext message */
	memset(buffer, 0, BUF_SIZE);
	memcpy(buffer, "abcdefghijklmnopqrstuvwxyz", 26);
	
	/* Crypt cleartext message */
	char *cryptbuf = crypt(cliargs.tkey, cliargs.skey, buffer);

	/* Compress cryped text */
	struct compress_text *compressbuf =
		compress_crypted_text(cryptbuf, strlen(cryptbuf));

	/* Send compressed crypted message */
	n = send(sockfd, compressbuf->text, compressbuf->size, 0);
	DIE_ERRNO(n < 0, "Cannot write to socket");
	DEBUG("Sent message %s", buffer);

	/* Receive confirmation */

	/* Close socket */	
	close(sockfd);

	return 0;
}
