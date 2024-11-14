/// Trey Rubino

#include <cstring>
#include <iostream>

#include "Session.h"
#include "Socket.h"
#include "Utility.h"

Session::Session() : cfd(-1), peer_addr_size(sizeof(peer_addr)) 
{
    memset(&peer_addr, 0, sizeof(peer_addr));
}

void Session::handle()
{
    /// send the begin string
    std::string begin_packet = "BEGIN";
    Socket::sendAll(this->cfd, begin_packet);

    /// recieve number of strings
    std::string num_strings = Socket::recvAll(this->cfd);
    
    ///
    if (sizeof(num_strings) < 0) {
        throw std::runtime_error("Expected number of strings to be more than 1.");
    }
    std::cout << "Sending " << num_strings << std::endl; 
}
