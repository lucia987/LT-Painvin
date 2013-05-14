#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>

#include "util.h"
#include "cli_args.h"
#include "socket.h"
#include "compress.h"

#define MAX_EVENTS	10
#define MAX_CLIENTS	5

int create_and_bind_socket(int portno)
{
	int listenfd, ret;
	struct sockaddr_in server_addr;

	/* Create socket */
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(listenfd < 0, "Cannot create socket");

	/* Initialize address structure */
	memset((char *) &server_addr, 0, sizeof server_addr);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(portno);
	
	/* Bind socket */
	ret = bind(listenfd, (struct sockaddr *)&server_addr, sizeof (struct sockaddr));
	DIE(ret < 0, "Cannot bind socket"); 

	return listenfd;
}

int main(int argc, char **argv)
{
	int epollfd, listenfd, ret;
	struct epoll_event event, *events;
	struct sockaddr_in client_addr;
	struct cliargs cliargs;

	cliargs = parse_cli_args(argc, argv);

	/* Create epoll descriptor */
	epollfd = epoll_create(10);

	/* Create, bind and listen on socket */
	listenfd = create_and_bind_socket(cliargs.portno);
	
	/* Make socket non blocking */
	make_non_block_socket(listenfd);
	DIE (!is_non_block(listenfd), "client sock is not nonblock");

	/* Listen on socket */
	listen(listenfd, MAX_CLIENTS);

	/* Add listenin socket to epoll file descriptor */
	event.data.fd = listenfd;
	event.events = EPOLLIN | EPOLLET;
	ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &event);
	DIE (ret == -1, "epoll_ctl");

	events = calloc(MAX_EVENTS, sizeof *events);

	/* The event loop */
	while (1) {
		int n, i;

		/* Wait for notification */
		n = epoll_wait(epollfd, events, MAX_EVENTS, -1);
		for (i = 0; i < n; i++)
		{
			if ((events[i].events & EPOLLERR) ||
				(events[i].events & EPOLLHUP) ||
				(!events[i].events & EPOLLIN))
			{
				/* An error occured */
				perror("epoll error\n");
				close(events[i].data.fd);
				continue;
			}
			else if (events[i].data.fd == listenfd)
			{
				/* Notification on listening socket */
				while(1)
				{
					struct sockaddr_in cliaddr;
					socklen_t clilen;
					int clientfd;
					char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

					clilen = sizeof (struct sockaddr);
						
					clientfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
					if (clientfd == -1)
					{
						if (errno == EAGAIN || errno == EWOULDBLOCK)
							break;
						else
							perror("accept");
							break;
					}
					ret = getnameinfo((struct sockaddr *)&cliaddr, clilen,
						hbuf, sizeof hbuf,
						sbuf, sizeof sbuf,
						NI_NUMERICHOST | NI_NUMERICSERV);
					if (!ret)
						DEBUG("Accepted connection on descriptor %2d"
							"(host=%s, port=%s).", clientfd, hbuf, sbuf);
					/* Make incoming socket non-blocking */
					make_non_block_socket(clientfd);

					/* Add incoming socket to epoll descriptor */
					event.data.fd = clientfd;
					event.events = EPOLLIN;
					ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, clientfd, &event);
					DIE(ret == -1, "epoll_ctl");
				}
				continue;
			}
			else
			{
				/* We have data to be read. We must read whatever data vailable, as we
				   are running on edge-triggered mode */
				int done = 0;
				while(1)
				{
					int count;
					char buffer[CRYPTBUF_SIZE+1];

					count = read(events[i].data.fd, buffer, sizeof buffer);
					if (count == -1)
					{
						/* If errno == EAGAIN, we have read all data */
						if (errno != EAGAIN)
						{
							perror("read");
							done = 1;
						}
						break;
					}
					else if (count == 0)
					{
						/* Remote end closed the connection */
						DEBUG("Remote end closed connection on fd %d",
							events[i].data.fd);
						done = 1;
						break;
					}
					buffer[count] = '\0';

					/* Decompress received message */
					char *decompbuf = de_compress_crypted_text(buffer, strlen(buffer));

					/* Decrypt decompressed received message */
					char *decryptbuf = de_crypt(cliargs.tkey, cliargs.skey, decompbuf);
					DEBUG("Received on fd %d message %s",
						events[i].data.fd, decryptbuf);
				}
				if (done)
				{
					close (events[i].data.fd);

				}

			}

		}
	}
	free (events);

	/* Close socket */
	close(listenfd);

	return 0;
}
