import socket
import threading

def coonnect_server(port):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind(("0.0.0.0", port))
    server.listen(7)
    print(f"Portul {port} e ascultat...")

    return server

def accept_connection(server):
    while True:
        client, address = server.accept()
        print(f"Conexiune de la {address}.")

        message = client.recv(1024).decode("utf-8")
        print(f"Mesaj: {message}")

        client.close()

port_1 = 13939
port_2 = 14726

socket_1 = coonnect_server(port_1)
socket_2 = coonnect_server(port_2)

thread_1 = threading.Thread(target=accept_connection, args=(socket_1,))
thread_2 = threading.Thread(target=accept_connection, args=(socket_2,))

thread_1.start()
thread_2.start()

thread_1.join()
thread_2.join()