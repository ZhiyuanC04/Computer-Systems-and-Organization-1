// Zhiyuan Chang vgs3qt
// HW10 Socket Chat

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>

#define BUFFER_SIZE 4096

void handleCommunication(int sockfd) {
    struct pollfd fds[2];
    fds[0].fd = sockfd;         // Socket file descriptor
    fds[0].events = POLLIN;     // Wait for data to read
    fds[1].fd = STDIN_FILENO;   // Standard input
    fds[1].events = POLLIN;     // Wait for data to read

    char buffer[BUFFER_SIZE];

    while (1) {
        int ret = poll(fds, 2, 60000); // 1-minute timeout
        if (ret > 0) {
            if (fds[0].revents & POLLIN) {
                // Reading from socket and writing to stdout
                ssize_t bytesRead = read(sockfd, buffer, BUFFER_SIZE);
                if (bytesRead > 0) {
                    write(STDOUT_FILENO, buffer, bytesRead);
                }
            }
            if (fds[1].revents & POLLIN) {
                // Reading from stdin and writing to socket
                ssize_t bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE);
                if (bytesRead > 0) {
                    write(sockfd, buffer, bytesRead);
                }
            }
        } 
        else if (ret == 0) {
            printf("Poll timeout\n");
        } 
        else {
            perror("Poll error");
            break;
        }
    }
    close(sockfd);
}

void runServer(int input) {
    // Create socket, bind to the port, listen for incoming connections
    // If port is 0, the OS will assign a random port
    // Accept connections and handle them accordingly
    // start by getting a random port from the ephemeral port range
    int port;
    port = input;
    if (port == 0) {
        // Pick a random port from the ephemeral port range if no command-line argument
        srandom(getpid()); // random seed based on this process's OS-assigned ID
        port = 0xc000 | (random() & 0x3fff); // random element of 49152–65535
    }

    // Create an address structure: IPv4 protocol, any IP address, on given port
    struct sockaddr_in ipOfServer;
    memset(&ipOfServer, 0, sizeof(struct sockaddr_in));
    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);
    ipOfServer.sin_port = htons(port);

    // Create a listener socket
    int listener = socket(AF_INET, SOCK_STREAM, 0);

    // Bind the listener socket to the address
    bind(listener, (struct sockaddr*)&ipOfServer, sizeof(ipOfServer));

    // Start listening for connections; suggest the OS queue up to 20
    listen(listener, 20);

    // Display server IP addresses and listening port
    // system("host portal08s"); // display all this computer's IP addresses
    system("host portal11");
    printf("The server is now listening on port %d\n", port);

    printf("Waiting for a connection\n");
    // Accept a single connection
    int connection = accept(listener, (struct sockaddr*)NULL, NULL);
    printf("Got a connection\n");

    close(listener);
    handleCommunication(connection);
    
    // return 0;
}

void runClient(const char *serverIP, int port) {

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddr;
    // memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_addr.s_addr = inet_addr(serverIP);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection Failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    handleCommunication(sockfd); // Function to handle communication
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // Run in server mode on a random port
        runServer(0);
    } 
    else if (argc == 2) {
        // Run in server mode on a specific port
        int port = atoi(argv[1]);
        runServer(port);
    } 
    else if (argc == 3) {
        // Run in client mode
        char *serverIP = argv[1];
        int port = atoi(argv[2]);
        runClient(serverIP, port);
    } 
    else {
        fprintf(stderr, "Usage: %s [port] or %s [server IP] [port]\n", argv[0], argv[0]);
        exit(1);
    }
    return 0;
}