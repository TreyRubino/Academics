/// Trey Rubino

#include <stdexcept>
#include <unistd.h>
#include <iostream>

#include "Parser.h"

Parser::Parser() : port("80"), file("") {}

void Parser::parse(int argc, char **argv) 
{
    int opt;
    while ((opt = getopt(argc, argv, "p:f:v")) != -1) {
        switch (opt) {
            case 'p':
                this->port = std::string(optarg);
                break;
            case 'f':
                this->file = std::string(optarg);
                break;
            default:
                std::cout << this->usage() << std::endl;
                throw std::runtime_error("Invalid argument provided");
        }
    }
}

std::string Parser::usage() 
{
    return "Usage of this program:\n"
           "-p <string> (required) port number. Default 80\n"
           "-f <string> (required) file to read string data from\n";
}
