build: client server

cli_args.o: cli_args.c cli_args.h
	gcc -c -g cli_args.c -o cli_args.o

client: socket.o client.o
	gcc -g socket.o client.o -o client

client.o: client.c
	gcc -g -c client.c -o client.o
 
server: socket.o server.o
	gcc -g socket.o server.o -o server

server.o: server.c
	gcc -g -c server.c -o server.o

socket.o: socket.c
	gcc -g -c socket.c -o socket.o

compress.o: compress.c
	gcc -g -c compress.c -o compress.o

main: substitute.o transpose.o crypt.o main.o
	gcc -g substitute.o transpose.o crypt.o main.o -o main

substitute.o: substitute.c substitute.h
	gcc -g -c substitute.c -o substitute.o

transpose.o: transpose.c transpose.h
	gcc -g -c transpose.c -o transpose.o

crypt.o: crypt.c crypt.h
	gcc -g -c crypt.c -o crypt.o

clean:
	rm *.o main client server
