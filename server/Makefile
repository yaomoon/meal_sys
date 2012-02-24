
all: socket.o server.o
	gcc server.o socket.o -o server
socket.o: socket.c
	gcc -c socket.c -o socket.o
server.o: server.c socket.h
	gcc -c server.c -o server.o

server: server.c
	gcc server.c -o server

clean:
	-rm server server.o socket.o
