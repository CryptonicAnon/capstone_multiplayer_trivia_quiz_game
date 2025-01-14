import socket

def main():
    HOST = socket.gethostname() # Server's host address
    PORT = 22000

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        # Connect to the server
        client_socket.connect((HOST, PORT))
        print(f"Connected to {HOST}:{PORT}")

        # Continue here for what the client is sending to the server.
        message = "Message from client"
        client_socket.send(message.encode())
        print(f"Sent: {message}")

        # Receive a response
        response = client_socket.recv(1024).decode()
        print(f"Server responded: {response}")

    finally:
        # Close the connection
        client_socket.close()
        print("Connection closed.")

if __name__ == "__main__":
    main()
