#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "util.h"
#include "socket.h"
#include "compress.h"

int main()
{
	int sockfd, n, ret;
	struct sockaddr_in server_addr;
	struct hostent *server;
	char buffer[BUF_SIZE];

	char *hostname = "localhost";

	/* Create TCP socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(sockfd < 0, "Cannot create socket");

/*
	make_non_block_socket(sockfd);
	DIE (!is_non_block(sockfd), "client sock is not nonblock");
*/
	/* Get server hostent struct */
	server = gethostbyname(hostname);
	DIE(server == NULL, "No such host");

	/* Initialize address structure */
	memset((char *) &server_addr, 0, sizeof server_addr);
	server_addr.sin_family = AF_INET;
	memcpy((char *)&server_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
	server_addr.sin_port = htons(PORTNO);
	
	/* Connect to server socket */
	ret = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	DIE(ret < 0, "Cannot connect to server");
	
	/* Send message */
	memset(buffer, 0, BUF_SIZE);
	memcpy(buffer, "abcdefghijklmnopqrstuvwxyz", 26); 

	printf("before send");
	n = send(sockfd, buffer, strlen(buffer), 0);
	DIE (n < 0, "Cannot write to socket");
	printf("after send %d\n", n);
	/* Receive confirmation */

	/* Close socket */	
	close(sockfd);

	printf("What just happened\n");
	return 0;
}
