/// Trey Rubino

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "Client.h"
#include "Utility.h"

Client::Client(Parser &parser) : Socket(parser) {}

void Client::connect()
{
    struct addrinfo hints{}, *res;
    memset(&hints, 0, sizeof(hints));   /// Initialize hints to zero
    hints.ai_family = AF_INET;          /// Use IPv4
    hints.ai_socktype = SOCK_STREAM;    /// Use TCP

    /// Resolve the hostname or IP address
    int status = getaddrinfo(this->parser.host.c_str(), this->parser.port.c_str(), &hints, &res);
    if (status != 0) {
        throw std::runtime_error("Failed to resolve hostname: " + std::string(gai_strerror(status)));
    }

    if (::connect(this->fd, res->ai_addr, res->ai_addrlen) == -1) {
        freeaddrinfo(res);              /// Free the address info on error
        throw std::runtime_error("Failed to connect: " + std::string(strerror(errno)));
    }

    freeaddrinfo(res);                  /// Free the address info after successful connection
}

void Client::begin() 
{
    std::string begin_packet = this->recvAll(this->fd);
    if (begin_packet != "BEGIN") {
        throw std::runtime_error("Expected \"BEGIN\" packet from server.");
    }
    std::cout << "Received \"BEGIN\"" << std::endl;
}

void Client::request()
{
    std::string request_packet = Utility::encodeInt32(this->parser.num_strings);
    sendAll(this->fd, request_packet);
    std::cout << "Sending " << this->parser.num_strings << std::endl;
}

void Client::receive() 
{
    /// for each string we requested, recv all the bytes, decode them, and output 
    for (int i = 0; i < this->parser.num_strings; ++i) {
        std::string random_string = this->recvAll(this->fd);
        std::cout << "Received string " << i+1 << ": " << random_string << std::endl;
    }
}

void Client::end()
{
    shutdown(this->fd, SHUT_WR);

    /// retrieve the end packet
    std::string end_packet = this->recvAll(this->fd);
    if (end_packet != "END") {
        throw std::runtime_error("Expected \"END\" packet from server.");
    }
}
