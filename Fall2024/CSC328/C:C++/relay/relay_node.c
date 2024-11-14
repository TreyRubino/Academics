/// Trey Rubino

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 4096

typedef struct {
    int port;
    char next_ip[16];
    int next_port;
    int is_exit_node;
} RelayConfig;

void *handle_connection(void *arg);

int start_relay(RelayConfig config) 
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    pthread_t thread_id;

    /// Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    /// Allow address reuse
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Setsockopt");
        exit(EXIT_FAILURE);
    }

    /// Bind to the specified port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(config.port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("[Relay %d] Listening on port %d\n", config.port, config.port);

    if (listen(server_fd, 10) < 0) {
        perror("Listen");
        exit(EXIT_FAILURE);
    }

    /// Accept incoming connections
    while (1) {
        socklen_t addrlen = sizeof(address);
        new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        if (new_socket < 0) {
            perror("Accept");
            continue;
        }

        /// Handle the connection in a new thread
        RelayConfig *client_config = malloc(sizeof(RelayConfig));
        *client_config = config;
        client_config->port = new_socket; // Overload port to pass socket
        if (pthread_create(&thread_id, NULL, handle_connection, client_config) != 0) {
            perror("Thread creation");
            free(client_config);
            continue;
        }
        pthread_detach(thread_id);
    }

    close(server_fd);
    return 0;
}

void *handle_connection(void *arg) 
{
    RelayConfig config = *(RelayConfig *)arg;
    int client_socket = config.port; /// Retrieve the client socket
    free(arg);

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    /// Read data from the client
    bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_read <= 0) {
        perror("Receive");
        close(client_socket);
        return NULL;
    }

    /// Simulate decryption (for this example, we'll just print the data)
    buffer[bytes_read] = '\0';
    printf("[Relay %d] Received data: %s\n", config.port, buffer);

    /// Log structured output
    if (config.is_exit_node) {
        printf("[Exit Relay %d] Final data: %s\n", config.port, buffer);
        /// Here you can add code to send data to the destination server
    } else {
        printf("[Relay %d] Forwarding to %s:%d\n", config.port, config.next_ip, config.next_port);

        /// Forward data to the next relay
        int next_socket;
        struct sockaddr_in next_address;

        if ((next_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("Next socket creation");
            close(client_socket);
            return NULL;
        }

        next_address.sin_family = AF_INET;
        next_address.sin_port = htons(config.next_port);

        if (inet_pton(AF_INET, config.next_ip, &next_address.sin_addr) <= 0) {
            perror("Invalid next IP address");
            close(client_socket);
            close(next_socket);
            return NULL;
        }

        if (connect(next_socket, (struct sockaddr *)&next_address, sizeof(next_address)) < 0) {
            perror("Connect to next relay");
            close(client_socket);
            close(next_socket);
            return NULL;
        }

        /// Send data to the next relay
        if (send(next_socket, buffer, bytes_read, 0) != bytes_read) {
            perror("Send to next relay");
        }

        close(next_socket);
    }

    close(client_socket);
    return NULL;
}

int main(int argc, char *argv[]) 
{
    if (argc < 5) {
        fprintf(stderr, "Usage: %s <port> <next_ip> <next_port> <is_exit_node>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    RelayConfig config;
    config.port = atoi(argv[1]);
    strncpy(config.next_ip, argv[2], sizeof(config.next_ip));
    config.next_port = atoi(argv[3]);
    config.is_exit_node = atoi(argv[4]);

    start_relay(config);

    return 0;
}
