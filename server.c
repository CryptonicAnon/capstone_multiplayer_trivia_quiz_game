#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "server.h"


#define PORT 22000
#define BUFFER_SIZE 1024

void* handle_client(void* client_socket_ptr) {
    int client_socket = *(int*)client_socket_ptr;
    char buffer[BUFFER_SIZE];
    FILE *QUESTIONS_FILE = fopen("questions.csv", "r");

    fgets(buffer, sizeof(buffer), QUESTIONS_FILE);

    if (fgets(buffer, sizeof(buffer), QUESTIONS_FILE) != "END_OF_QUIZ");
    {
        char *data = strtok(buffer, ",");
    }
    // Communicate with the client
    for (int i = 0; i < 3; i++) {
        memset(buffer, 0, BUFFER_SIZE);
        read(client_socket, buffer, BUFFER_SIZE);
        printf("Client says: %s\n", buffer);

        // Send a response
        char response[BUFFER_SIZE];
        snprintf(response, sizeof(response), "Server received: %s", buffer);
        send(client_socket, response, strlen(response), 0);
    }

    // Close the client socket
    close(client_socket);
    free(client_socket_ptr);
    return NULL;
}

int main()
{
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Create the server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Socket successfully created..\n");
    }

     // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for connections
    if (listen(server_socket, 5) == -1)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Server is listening on port %d...\n", PORT);

    while (1)
    {
        // Accept a connection
        int* client_socket_ptr = malloc(sizeof(int));
        *client_socket_ptr = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (*client_socket_ptr == -1)
        {
            perror("Accept failed");
            free(client_socket_ptr);
            continue;
        }
        // Create a new thread to handle the client
        pthread_t client_thread;
        pthread_create(&client_thread, NULL, handle_client, client_socket_ptr);
        pthread_detach(client_thread);
    }
    close(server_socket);
    return 0;
}