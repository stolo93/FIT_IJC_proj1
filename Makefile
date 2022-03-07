CC=gcc
Cflags = -g -std=c11 -pedantic -Wall -Wextra

all: erat_main

erat_main: error.o bitset.o
	$(CC) $(Cflags) errro.o bitset.o erat.c -o erat_main

error.o: error.c
	$(CC) $(Cflags) -c error.c

bitset.o: bitset.c
	$(CC) $(Cflags) -c bitset.c

clean:
	rm *.o