import socket

def main():
    host = '127.0.0.1'
    port = 22000

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)