import socket

BUFFERSIZE=1024
HOST = socket.gethostname() # Server's host address
PORT = 22000

def main():
    continue_game = True
    score = 0
    # Create a socket object
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        # Connect to the server
        client_socket.connect((HOST, PORT))
        print(f"Connected to {HOST}:{PORT}")

        while(continue_game):
            question = client_socket.recv(1024).decode()
            correct_answer = client_socket.recv(1024).decode()
            print(question)
            answer = input("answer the question: ")
            client_socket.send(answer)

            print(f"The correct answer was: {correct_answer}")

            if answer == correct_answer:
                print("You got the question right!")
                score += 1
            elif answer != correct_answer:
                print("You lost GG lbitchoser.")
                client_socket.close()
                print("Connection closed.")
                quit()
            else:
                print("this didnt work")

            

    finally:
        # Close the connection
        client_socket.close()
        print("Connection closed.")

if __name__ == "__main__":
    main()
