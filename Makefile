CC = gcc
CFLAGS = -Wall -Wextra -g

runclient: client
	./client --server=localhost --port=8000 --tkey="natang" --skey="ph0qg64mea1yl2nofdxkr3cvs5zw7bj9uti8" --file=input.txt

runserver: server
	./server --port=8000 --tkey="natang" --skey="ph0qg64mea1yl2nofdxkr3cvs5zw7bj9uti8" --file=output.txt

build: client server

client: substitute.o transpose.o cli_args_client.o crypt.o compress.o client.o

client.o: client.c
 
server: socket.o transpose.o substitute.o cli_args.o crypt.o compress.o server.o

server.o: server.c

socket.o: socket.c

cli_args.o: cli_args.c cli_args.h

cli_args_client.o: cli_args.c cli_args.h
	$(CC) $(CFLAGS) -c -DIS_CLIENT=1 -o $@ $<

compress.o: compress.c compress.h

substitute.o: substitute.c substitute.h

transpose.o: transpose.c transpose.h

crypt.o: crypt.c crypt.h

clean:
	rm *.o main client server
