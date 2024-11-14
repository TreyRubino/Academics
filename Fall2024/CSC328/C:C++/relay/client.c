/// Trey Rubino

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 4096

void send_data(const char *entry_ip, int entry_port, const char *data) 
{
    int sock;
    struct sockaddr_in entry_address;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation");
        exit(EXIT_FAILURE);
    }

    entry_address.sin_family = AF_INET;
    entry_address.sin_port = htons(entry_port);

    if (inet_pton(AF_INET, entry_ip, &entry_address.sin_addr) <= 0) {
        perror("Invalid entry IP address");
        close(sock);
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&entry_address, sizeof(entry_address)) < 0) {
        perror("Connect to entry node");
        close(sock);
        exit(EXIT_FAILURE);
    }

    /// Simulate layered encryption (for this example, we'll send data as-is)
    if (send(sock, data, strlen(data), 0) != (ssize_t)strlen(data)) {
        perror("Send to entry node");
    } else {
        printf("[Client] Data sent to entry node.\n");
    }

    close(sock);
}

int main() 
{
    char data[BUFFER_SIZE];

    // Get user input
    printf("Enter data to send: ");
    if (fgets(data, sizeof(data), stdin) == NULL) {
        perror("Input error");
        exit(EXIT_FAILURE);
    }

    /// Remove newline character
    data[strcspn(data, "\n")] = '\0';

    /// Send data to entry node
    send_data("127.0.0.1", 15001, data);

    return 0;
}
