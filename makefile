compile: server client fserver

server: server.c pipe_networking.c
	gcc server.c pipe_networking.c -o server

client: client.c pipe_networking.c
	gcc client.c pipe_networking.c -o client

fserver: fserver.c pipe_networking.c
	gcc fserver.c pipe_networking.c -o fserver

clean:
	rm -f server client fserver
	rm *~