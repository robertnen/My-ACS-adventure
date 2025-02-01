import socket

server_ip = "isc2024.1337.cx"
port = 18
message = b"18u"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto(message, (server_ip, port))
data, addr = sock.recvfrom(1024)  # Wait for a response
print("Received:", data.decode())
