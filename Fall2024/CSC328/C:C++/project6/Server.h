#ifndef SERVER_H
#define SERVER_H

#include "Socket.h"

class Server : public Socket 
{
public:
    Server::Server(Parser &parser) : Socket(parser) {}

    /// Binds main socket and error checking
    /// @throws 	std::runtime_error
    void bind();

    /// listen
    /// @brief Listens to main socket connection and error checking
    /// @throws 	std::runtime_error
    void listen();

    /// accept
    /// @brief Accepts connects to the main socket and updates the Session class
    /// @param 		Session &session	- pointer to the Session object
    /// @throws		std::runtime_error
    void accept(Session &session);

private: 

    /// fork
    /// @brief  
    /// @param session 
    void fork(Session &session);
};

#endif // SERVER_H
