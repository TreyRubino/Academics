/// Trey Rubino

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "Socket.h"

Socket::Socket(Parser &parser) : parser(parser) 
{
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
   	throw std::runtime_error("Failed to create socket: " + std::string(strerror(errno)));
    }
}

void Socket::bind() 
{
    struct sockaddr_in server_addr{}; 			  	/// empty struct
    server_addr.sin_family = AF_INET; 			  	/// IPv4
    server_addr.sin_port = htons(std::stoi(parser.port)); 	/// convert port to int and then to network byte order
    server_addr.sin_addr.s_addr = INADDR_ANY; 			/// allows listening across all interfaces (loopback, public, etc)

    if (::bind(this->fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        throw std::runtime_error("Failed to bind: " + std::string(strerror(errno))); 
    }
}

void Socket::listen() 
{
    if (::listen(this->fd, 10) == -1) {
  	throw std::runtime_error("Failed on listen: " + std::string(strerror(errno)));
    }
}

void Socket::accept(Session &session) 
{
    session.peer_addr_size = sizeof(session.peer_addr);
    session.cfd = ::accept(this->fd, (struct sockaddr *)&session.peer_addr, &session.peer_addr_size);
    if (session.cfd == -1) {
        throw std::runtime_error("Failed to accept: " + std::string(strerror(errno)));   
    }
}

void Socket::close(int fd) 
{
    if (fd == -1) {
	::close(this->fd);
    } else {
	::close(fd);
    }
}

std::string Socket::recvAll(int client_fd) 
{
    const size_t buffer_size = 4096;
    char buffer[buffer_size];
    std::string result;
    ssize_t bytes_received;

    while ((bytes_received = recv(client_fd, buffer, buffer_size - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        result += buffer;
        if (static_cast<size_t>(bytes_received) < buffer_size - 1) {
            break;  /// No more data to read
        }
    }

    if (bytes_received == -1) {
        throw std::runtime_error("Failed to recv: " + std::string(strerror(errno)));
    }

    return result;
}

void Socket::sendAll(int client_fd, const std::string &message) 
{
    const char* buffer = message.c_str();
    size_t len = message.size();
    size_t total = 0;
    ssize_t bytes_sent;

    while (total < len) {
        bytes_sent = send(client_fd, buffer + total, len - total, 0);
        if (bytes_sent == -1) {
            throw std::runtime_error("Failed on send: " + std::string(strerror(errno)));
        }
        total += bytes_sent;
    }
}
