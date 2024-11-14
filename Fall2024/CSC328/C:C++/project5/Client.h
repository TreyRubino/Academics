/// Trey Rubino

#ifndef CLIENT_H
#define CLIENT_H

#include "Socket.h"

class Client : public Socket 
{
    public:

    Client(Parser &parser);

    /// connect
    /// Connects a client to the socket and performs error checking
    /// @throws     std::runtime_error
    void connect();

    /// begin
    /// Receives the "BEGIN" packet from the server and validates its content
    /// @throws     std::runtime_error if the "BEGIN" packet is missing or incorrect
    void begin();

    /// request
    /// Sends a request packet to the server specifying the number of strings to receive
    /// @throws     std::runtime_error if sending the packet fails
    void request();

    /// receive
    /// Receives the requested number of string packets from the server
    /// Decodes and prints each string to the console
    /// @throws     std::runtime_error if any packet is missing or corrupted
    void receive();

    /// end 
    /// Receives the "END" packet from the server and validates its content
    /// @throws     std::runtime_error if the "END" packet is missing or incorrect
    void end();
};

#endif // CLIENT_H
