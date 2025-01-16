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
    printf("\nSTARTED HANDLE_CLIENT FUNCTION\n");
    int client_socket = *(int*)client_socket_ptr;
    char buffer[BUFFER_SIZE];
    FILE *QUESTIONS_FILE = fopen("../questions.csv", "r");
    if (QUESTIONS_FILE == NULL)
    {
    perror("Failed to open questions.csv");
    close(client_socket);
    free(client_socket_ptr);
    return NULL;
    }

    printf("\nwe hit point 1.2\n");
    fgets(buffer, sizeof(buffer), QUESTIONS_FILE);
    fgets(buffer, sizeof(buffer), QUESTIONS_FILE);
    printf("\nwe hit point 1\n");

    do
    {
        printf("\nENTERED WHILE LOOP\n");
        // Communicate with the client
        char *data = strtok(buffer, ",");
        while (data != NULL)
        {
            printf("Sent: %s\n", data);
            send(client_socket, data, strlen(data), 0);
            usleep(500000);
            data = strtok(NULL, ",");
        }
        if (fgets(buffer, sizeof(buffer), QUESTIONS_FILE) == "END_OF_QUIZ")
        {
            break;
        }
        printf("Going to check the do while end.");
    } while (read(client_socket, buffer, BUFFER_SIZE));

    printf("I am here.");
    read(client_socket, buffer, BUFFER_SIZE);
    printf(buffer);

    // Close the client socket
    close(client_socket);
    free(client_socket_ptr);
    return NULL;
}

int socketLogic()
{
    printf("\nSTARTD MAIN FUNCTION\n");
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

    printf("\nwe hit point 01\n");
    // Start listening for connections
    if (listen(server_socket, 5) == -1)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Server is listening on port %d...\n", PORT);

    printf("\nwe hit point 02\n");
    while (1)
    {
        // Accept a connection
        int* client_socket_ptr = malloc(sizeof(int));
        *client_socket_ptr = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        printf("\nwe hit point 03\n");
        if (*client_socket_ptr == -1)
        {
            perror("Accept failed");
            free(client_socket_ptr);
            continue;
        }
        printf("\nwe hit point 04\n");
        // Create a new thread to handle the client
        pthread_t client_thread;
        pthread_create(&client_thread, NULL, handle_client, client_socket_ptr);
        printf("\nwe hit point 05\n");
        pthread_detach(client_thread);
    }

    printf("\nwe hit point 06\n");
    close(server_socket);
    return 0;
}

main()
{
    socketLogic();
}