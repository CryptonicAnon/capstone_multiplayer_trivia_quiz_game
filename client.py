import socket
import time

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

        # username = input("Please select a username: ")

        while(continue_game):
            question = client_socket.recv(1024).decode()
            answer_a = str(client_socket.recv(1024).decode())
            answer_b = str(client_socket.recv(1024).decode())
            answer_c = str(client_socket.recv(1024).decode())
            answer_d = str(client_socket.recv(1024).decode())
            correct_answer = client_socket.recv(1024).decode()
            correct_answer = correct_answer.strip()
            print(question)
            answer = input("answer the question: ")
            answer = answer.upper()

            print(f"Question: {question}")
            print(f"Answer A: {answer_a}")
            print(f"Answer B: {answer_b}")
            print(f"Answer C: {answer_c}")
            print(f"Answer D: {answer_d}")
            print(f"{answer}")
            print(f"The correct answer was: {correct_answer}")

            if answer == correct_answer:
                print("You got the question right!")
                score += 1
                print(f"Your score is now: {score}")
            elif answer != correct_answer:
                print("You lost GG lbitchoser.")
            else:
                print("this didnt work")
            client_socket.send(answer.encode("utf-8"))

        game_over = client_socket.recv(1024).decode()
        print(game_over)

        client_socket.send(score.encode("utf-8"))

        final_scores = client_socket.recv(1024).decode()
        final_scores = final_scores.split()
        final_scores = final_scores.sort()
        for i in range(len(final_scores)):
            print(f"{i}th place got: {final_scores[i]}")

    finally:
        # Close the connection
        client_socket.close()
        print("Connection closed.")

if __name__ == "__main__":
    main()
