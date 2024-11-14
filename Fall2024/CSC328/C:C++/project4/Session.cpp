/// Trey Rubino

#include <cstring>

#include "Session.h"

Session::Session() : cfd(-1), peer_addr_size(sizeof(peer_addr)) 
{
    memset(&peer_addr, 0, sizeof(peer_addr));
}
