#include <netdb.h>
#include <stdio.h>
#include <string.h>

#include "socket_utility.h"
 
const char REQUEST_TEMPLATE[] = "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n";

const int REQUEST_SIZE = 1024;
const int RESPONSE_SIZE = 4096;

/// socket_connect implementation
int socket_connect(Options *options, struct addrinfo **addr_list)
{
    	struct addrinfo hints, *current_addr;
    	int sockfd;
    
    	memset(&hints, 0, sizeof(hints)); /// initial properties of addrinfo with 0
	hints.ai_family = AF_INET; /// flag to use ipv4
	hints.ai_socktype = SOCK_STREAM; /// flag to use TCP

	int status = getaddrinfo(options->host, options->port, &hints, addr_list); 
	if (status != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		return -1;
	}	

	if (options->verbose == 1) {
		printf("Socket created successfully for host %s on port %s\n", options->host, options->port);
	}

	/// addr_list is a pointer to a pointer to the head of a linked-list. 
	/// We want to traverse the linked-list visiting each element (starting at the head), 
	/// for as long as the current_addr does not equal NULL indicating the end of the list,
	/// and setting the current_addr to the pointer to the next element in the list each iteration.
	for (current_addr = *addr_list; current_addr != NULL; current_addr = current_addr->ai_next) {
		sockfd = socket(current_addr->ai_family, current_addr->ai_socktype, 0);
		if (sockfd == -1) {
			perror("sock");
			continue; /// try the next entry in the linked list
		}
		
		if (connect(sockfd, current_addr->ai_addr, current_addr->ai_addrlen) != -1) {
			break; /// succesfully connected to the socket. stop attempting to connect
		}
	}
	
	if (current_addr == NULL) {
		fprintf(stderr, "Failed to connect\n");
		return -1;
	}

    	return sockfd;
}

/// socket_send implementation
int socket_send(Options *options, int sockfd)
{   
	char request[REQUEST_SIZE];
	int request_length = snprintf(request, sizeof(request), REQUEST_TEMPLATE, options->file_path, options->host);

	if (options->verbose == 1) {
		printf("HTTP Request:\n%s\n", request);		
	}

	if (send(sockfd, request, request_length, 0) == -1) {
		perror("send"); 
		return -1;
	}

   	 return 0;
}

int socket_receive(int sockfd, int verbose) 
{
    	/// receive the HTTP response with recv
	char response_buffer[RESPONSE_SIZE];
	int bytes_received;
	
	if (verbose == 1) {
		printf("HTTP Response:\n");
	}

	while ((bytes_received = recv(sockfd, response_buffer, sizeof(response_buffer) - 1, 0)) > 0) {
		response_buffer[bytes_received] = '\0';
		
		if (verbose == 1) {
			printf("%s", response_buffer);
		}
	}

	if (bytes_received == -1) {
		perror("recv");
        	return -1;
	}
    
	return 0;  	
}
