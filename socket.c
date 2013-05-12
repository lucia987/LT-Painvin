#include <fcntl.h>
#include <stdio.h>

#include "util.h"
#include "socket.h"

void make_non_block_socket(int sockfd)
{
	int flags, ret;

	/* Get socket flags */
	flags = fcntl(sockfd, F_GETFL, 0);
	DIE(flags == -1, "fcntl get flags");
	
	/* Make socket nonblocking by changing flags */
	ret = fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
	DIE(ret == -1, "fcntl set flags");
}

int is_non_block(int sockfd)
{
	int flags;

	flags = fcntl(sockfd, F_GETFL, 0);
	if (flags & O_NONBLOCK)
		return 1;
	else return 0;
}
