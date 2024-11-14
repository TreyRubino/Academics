#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "Server.h"
#include "Session.h"

void Server::bind() 
{
    struct sockaddr_in server_addr{}; 			  	                /// empty struct
    server_addr.sin_family      = AF_INET; 			  	            /// IPv4
    server_addr.sin_port        = htons(std::stoi(parser.port));    /// convert port to int and then to network byte order
    server_addr.sin_addr.s_addr = INADDR_ANY; 			            /// allows listening across all interfaces (loopback, public, etc)

    if (::bind(this->fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        throw std::runtime_error("Failed to bind: " + std::string(strerror(errno))); 
    }
}

void Server::listen() 
{
    if (::listen(this->fd, 10) == -1) {
  	    throw std::runtime_error("Failed on listen: " + std::string(strerror(errno)));
    }
}

void Server::accept(Session &session) 
{
    session.peer_addr_size = sizeof(session.peer_addr);
    session.cfd = ::accept(this->fd, (struct sockaddr *)&session.peer_addr, &session.peer_addr_size);
    if (session.cfd == -1) {
        throw std::runtime_error("Failed to accept: " + std::string(strerror(errno)));   
    }

    this->fork(session);    /// handle all connections as different processes
}

void Server::fork(Session &session)
{
    pid_t pid = ::fork();

    if (pid < 0) { /// error
        throw std::runtime_error("Failed to fork: " + std::string(strerror(errno)));
    } else if (pid == 0) { /// child
        session.handle();
        close(session.cfd);
        exit(0);
    } else { /// parent
        close(session.cfd);
    }
}

