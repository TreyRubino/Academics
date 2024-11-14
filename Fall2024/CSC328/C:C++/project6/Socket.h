/// Trey Rubino

#ifndef SOCKET_H
#define SOCKET_H

#include "Parser.h"

/// Agumented version of Dr. Schwesinger's Socket class.
class Socket 
{
    protected:

    int fd; 		    /// Main socket file discriptor             
    Parser &parser; 	/// Parser dependency for command line options

    public:
	
    /// constructor
    /// @brief Constructor. Sets Parser reference and this->fd
    /// @param 		Parser &parser		- pointer to the Parser object 
    Socket(Parser &parser);

    /// close
    /// @brief Handles closing of the main and client socket
    /// @param 		int fd - flag to close main socket
    void close(int fd = -1);  

    /// recvAll
    /// @brief Augmented version of Dr. Schwesinger's recvAll
    /// @param  	int client_fd		- connected client file descriptor
    /// @return 	std::string		- recived request from client
    /// @throws 	std::runtime_error
    static std::string recvAll(int client_fd);

    /// sendAll
    /// @brief Augmented version of Dr. Schwesinger's sendAll
    /// @param  	int client_fd		- connect client file descriptor
    /// @param		std::string &message 	- response message to send to client
    /// @throws 	std::runtime_error
    static void sendAll(int client_fd, const std::string &message);
};

#endif
