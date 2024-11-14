/// Trey Rubino

#ifndef SOCKET_UTILITY_H
#define SOCKET_UTILITY_H

#include "utility.h"

/// socket_connect
/// @brief Handles the error handling and connection to the socket. Returns successful connection.
/// @param	Options *options		- pointer to the typedef Options struct 
/// @param	struct addrinfo **addr_list	- pointer to the pointer to the addrinfo head of the linked list 
/// @return 	int sockfd			- connected socket file describer
int socket_connect(Options *options, struct addrinfo **addr_list);

/// socket_send
/// @brief Handles the error handling, construction of the request payload, and sending the request.
/// @param	Options *options	- pointer to the programs command line arugments
/// @param	int sockfd		- the connected socket
/// @return	int			- 0 for success, -1 for error 
int socket_send(Options *options, int sockfd);

/// socket_receive
/// @brief Handles the error handling, and buffering of the response payload.
/// @param	int sockfd	- the connected socket
/// @param	int verbose	- program option for verbose mode. i.e. 1 or 0
/// @return	int 		- 0 for success, -1 for error
int socket_receive(int sockfd, int verbose);

#endif
