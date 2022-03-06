CC=gcc
Cflags = -g -std=c11 -pedantic -Wall -Wextra

all: error bitset erat.c
	$(CC) $(Cflags) error.o bitset.o erat.c -o erat

error: error.c
	$(CC) $(Cflags) -c error.c

bitset: bitset.c
	$(CC) $(Cflags) -c bitset.c

clean:
	rm bitset.o error.o