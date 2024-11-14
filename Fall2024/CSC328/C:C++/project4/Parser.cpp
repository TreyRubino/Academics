/// Trey Rubino

#include <stdexcept>
#include <unistd.h>
#include <iostream>

#include "Parser.h"

Parser::Parser() : port(""), directory("./"), verbose(false) {}

void Parser::parse(int argc, char **argv) 
{
    int opt;
    while ((opt = getopt(argc, argv, "p:d:v")) != -1) {
        switch (opt) {
            case 'p':
                this->port = std::string(optarg);
                break;
            case 'd':
                this->directory = std::string(optarg);
                break;
            case 'v':
                this->verbose = true;
                break;
            default:
                throw std::runtime_error("Invalid argument provided");
        }
    }
    if (this->port.empty()) {
        throw std::runtime_error("Port is required. Use -p <port>.");
    }
}

std::string Parser::usage() 
{
    return "Usage of this program:\n"
           "-p <string> (required) port number to use\n"
           "-d <string> (optional) path to the directory to serve files from.\n"
           "-v (optional) flag to set verbose mode\n";
}
