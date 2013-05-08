LD_FLAGS = -lpthread

build: main

main: substitute.o transpose.o crypt.o main.o
	gcc -g substitute.o transpose.o crypt.o main.o -o main

substitute.o: substitute.c substitute.h
	gcc -g -c substitute.c -o substitute.o

transpose.o: transpose.c transpose.h
	gcc -g -c transpose.c -o transpose.o

crypt.o: crypt.c crypt.h
	gcc -g -c crypt.c -o crypt.o

main.o: main.c
	gcc -g -c main.c -o main.o

clean:
	rm *.o main
