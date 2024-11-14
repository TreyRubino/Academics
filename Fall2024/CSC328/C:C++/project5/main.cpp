/// @author             Trey Rubino
/// @major              Computer Science and Mathematics
/// @creationdate       2024-11-01
/// @duedate            2024-11-08
/// @course             CSC 328 010
/// @professor          Dr. Schwesinger
/// @project            #5
/// @filename           main.cpp
/// @brief              Practicing endianness

#include <iostream>
#include <cstring>

#include "Parser.h"
#include "Socket.h"
#include "Utility.h"
#include "Client.h"

int main(int argc, char **argv) 
{
    try {
        Parser parser;
        parser.parse(argc, argv);

        Client client(parser);

        client.connect();
        client.begin();
        client.request();
        client.receive();
        client.end();       /// shutdown 

        client.close();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
