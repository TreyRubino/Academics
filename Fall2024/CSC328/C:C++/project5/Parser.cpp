/// Trey Rubino

#include <stdexcept>
#include <unistd.h>
#include <iostream>

#include "Parser.h"

Parser::Parser() : port("80"), host("localhost"), num_strings(1) {}

void Parser::parse(int argc, char **argv) 
{
    int opt;
    while ((opt = getopt(argc, argv, "p:h:n:v")) != -1) {
        switch (opt) {
            case 'p':
                this->port = std::string(optarg);
                break;
            case 'h':
                this->host = std::string(optarg);
                break;
            case 'n':
                this->num_strings = atoi(optarg);
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
           "-h <string> (required) target host. Default localhost\n"
           "-n <int> (optional) number of strings to request. Default 1 \n";
}
