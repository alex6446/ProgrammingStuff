import socket
import time

HEADERSIZE = 10

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((socket.gethostname(), 1234))
s.listen(5)

while True:
	clientsocket, adress = s.accept()
	print(f"Connection from {adress} has been established!")
	
	msg = "Welcome to the server!"
	msg = f"{len(msg):<{HEADERSIZE}}"+msg

	clientsocket.send(bytes(msg, 'utf-8'))

	while True:
		time.sleep(3)
		msg = f'The time is! {time.time()}'
		msg = f'{len(msg):<{HEADERSIZE}}'+msg
		clientsocket.send(bytes(msg, 'utf-8'))
