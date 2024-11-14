/// @author             Trey Rubino
/// @major              Computer Science and Mathematics
/// @creationdate       2024-11-10
/// @duedate            2024-11-15
/// @course             CSC 328 010
/// @professor          Dr. Schwesinger
/// @project            #6
/// @filename           main.cpp
/// @brief              Practicing endianness (Server side multi processing)

#include <iostream>
#include <cstring>

#include "Parser.h"
#include "Socket.h"
#include "Session.h"
#include "Utility.h"
#include "Server.h"

int main(int argc, char **argv) 
{
    try {
        Parser parser;
        parser.parse(argc, argv);

        Server server(parser);

        server.bind();
        server.listen();
       
        while (true) {
            Session session;
            server.accept(session);     /// handles each connection in parallel.
        }

        server.close();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
