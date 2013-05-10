run: build
	./client

build: client server main

client: compress.o client.o
	gcc -g compress.o client.o -o client

client.o: client.c
	gcc -g -c client.c -o client.o
 
server: compress.o server.o
	gcc -g compress.o server.o -o server

compress.o: compress.c
	gcc -g -c compress.c -o compress.o

server.o: server.c
	gcc -g -c server.c -o server.o

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
