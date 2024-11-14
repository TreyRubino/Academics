/// Trey Rubino

#include <arpa/inet.h>
#include <sys/stat.h>
#include <fstream>
#include <sstream>

#include "Utility.h"

std::string Utility::encodeInt32(int num) 
{
    uint32_t net_order = htonl(num);    /// host to network byte order (long)             
    return std::string(reinterpret_cast<char*>(&net_order), sizeof(net_order));       
}