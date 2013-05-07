LD_FLAGS = -lpthread

build: main

main: keysquare.o adfgvx_crypt.o main.o
	gcc keysquare.o main.o -o main

keysquare.o: keysquare.c keysquare.h
	gcc -c keysquare.c -o keysquare.o

adfgvx_crypt.o: adfgvx_crypt.c adfgvx_crypt.h
	gcc -c adfgvx_crypt.c -o adfgvx_crypt.o

main.o: main.c
	gcc -c main.c -o main.o

clean:
	rm *.o main
