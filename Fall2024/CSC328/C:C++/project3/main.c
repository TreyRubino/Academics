/// @author		Trey Rubino
/// @major		Computer Science and Mathematics
/// @creationdate	2024-09-29
/// @duedate		2024-10-04
/// @course		CSC 328 010
/// @professor		Dr. Schwesinger
/// @project		#3
/// @filename		main.c
/// @brief		Simple web client. Program will connect to socket, build GET request from command line arguments
///		 	recieves response and closes socket.

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "utility.h"
#include "socket_utility.h"

int main(int argc, char **argv)
{ 
	Options options = { .host = "localhost", .port = "80", .file_path = "/", .verbose = 0 };
	
	parser(argc, argv, &options); /// parse command line options
	
	struct addrinfo *addr_list;
	int sockfd = socket_connect(&options, &addr_list);
	if (sockfd == -1) {
		freeaddrinfo(addr_list); /// free memory allocated by getaddrinfo
		exit(EXIT_FAILURE);
	}

	if (socket_send(&options, sockfd) == -1) {
		perror("send"); /// use perror since send sets errono
		freeaddrinfo(addr_list); /// free memory allocated by getaddrinfo
		exit(EXIT_FAILURE);
	}

	if (socket_receive(sockfd, options.verbose) == -1) {
		perror("receive"); /// use perror since recv sets errono		
		freeaddrinfo(addr_list); /// free memory allocated by getaddrinfo
		exit(EXIT_FAILURE);
	}
	
	freeaddrinfo(addr_list); /// free memory allocated by getaddrinfo
	close(sockfd); /// close sock connection

	return 0;	
}
