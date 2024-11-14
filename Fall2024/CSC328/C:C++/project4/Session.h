/// Trey Rubino

#ifndef SESSION_H
#define SESSION_H

#include <sys/socket.h>
#include <netinet/in.h>

/// Custom session class for easy and clean access to connected clients info.
struct Session 
{
    struct sockaddr_in peer_addr;  /// client's address
    int cfd;                       /// client file descriptor
    socklen_t peer_addr_size;      /// size of the client's address

    /// constructor
    Session();
};

#endif
