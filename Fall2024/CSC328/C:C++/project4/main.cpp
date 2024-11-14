/// @author             Trey Rubino
/// @major              Computer Science and Mathematics
/// @creationdate       2024-10-08
/// @duedate            2024-10-11
/// @course             CSC 328 010
/// @professor          Dr. Schwesinger
/// @project            #4
/// @filename           main.cpp
/// @brief              Simple web server. Project will connect to socket, bind, listen
///			accept requests, build and return response data.

/// This program uses camelCase and PascelCase syntax for functions and structures
/// rather than snake_case since we are using C++. 

#include <iostream>
#include <cstring>

#include "Parser.h"
#include "Session.h"
#include "Socket.h"
#include "Utility.h"

/// handleRequest
/// @brief Helper function to handle the requests while the server lives.
void handleRequest(Session &session, const Parser &parser, Socket &socket) 
{
    std::string request = socket.recvAll(session.cfd);

    if (parser.verbose) {
        std::cout << "Received Request:\n" << request << std::endl;
    }

    /// parse the sting to extract file path. starting at index 5 which is after GET plus a space
    /// and extracts all the way to the next space right before HTTP. find(" ', 5) takes in account the entire,
    /// which is why we subtract 5 for the readed "visited" indexes. 
    std::string file_path = parser.directory + request.substr(5, request.find(" ", 5) - 5);
    std::string response = Utility::generateResponse(parser.directory, file_path);

    socket.sendAll(session.cfd, response);
    socket.close(session.cfd);
}

/// Main program loop.
int main(int argc, char **argv) 
{
    try {
        Parser parser;
        parser.parse(argc, argv);

        Socket socket(parser);

        socket.bind();
        socket.listen();

        while (true) {
            Session session;
            socket.accept(session);
            handleRequest(session, parser, socket);
        }

	socket.close();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
