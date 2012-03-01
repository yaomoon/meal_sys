
all: socket.o server.o sqlite.o
	gcc server.o socket.o sqlite.o -o server -pthread -lsqlite3
socket.o: socket.c
	gcc -c socket.c -pthread -o socket.o
server.o: server.c socket.h
	gcc -c server.c -o server.o
sqlite.o: sqlite.c
	gcc -c sqlite.c -lsqlite3 -o sqlite.o

server: server.c
	gcc server.c -o server

clean:
	-rm server server.o socket.o
