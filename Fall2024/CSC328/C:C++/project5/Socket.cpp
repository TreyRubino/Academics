/// Trey Rubino

#include <iostream>
#include <iomanip>
#include <cstring>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>

#include "Socket.h"

Socket::Socket(Parser &parser) : parser(parser) 
{
    if ((this->fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
   	    throw std::runtime_error("Failed to create socket: " + std::string(strerror(errno)));
    }
}

void Socket::close() 
{
    ::close(this->fd);
}

std::string Socket::recvAll(int client_fd) 
{
    /// Read the 2-byte length prefix
    unsigned short length_net;
    
    /// WAITALL to make sure we receive all bytes. Could also be used below but its good to know the explicit recvAll logic
    ssize_t bytes_received = recv(client_fd, &length_net, sizeof(length_net), MSG_WAITALL);     
    if (bytes_received != sizeof(length_net)) {
        throw std::runtime_error("Failed to receive packet length" + std::string(strerror(errno)));
    }

    unsigned short length = ntohs(length_net);          /// Convert length from network byte order to host byte order
    std::vector<char> buffer(length);                   /// Allocate buffer for the data

    /// Read the data
    size_t total_received = 0;
    while (total_received < length) {
        bytes_received = recv(client_fd, buffer.data() + total_received, length - total_received, 0);
        if (bytes_received <= 0) {
            throw std::runtime_error("Failed to receive packet data" + std::string(strerror(errno)));
        }
        total_received += bytes_received;
    }

    return std::string(buffer.begin(), buffer.end());   /// Convert buffer to string and return
}

void Socket::sendAll(int client_fd, const std::string &message) 
{ 
    const char* buffer = message.c_str();
    size_t length = message.size();
    size_t total_sent = 0;
    ssize_t bytes_sent;

    while (total_sent < length) {
        bytes_sent = send(client_fd, buffer + total_sent, length - total_sent, 0);
        if (bytes_sent == -1) {
            throw std::runtime_error("Failed on send: " + std::string(strerror(errno)));
        }
        total_sent += bytes_sent;
    }
}
