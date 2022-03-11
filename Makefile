CC=gcc
Cflags = -g -std=c11 -pedantic -Wall -Wextra

run: all
	./primes && ./primes-i

run_check: all
	time ./primes | factor && time ./primes-i | factor
	rm *.o primes primes-i	

all: primes steg

primes: error.o	eratosthenes.o
	$(CC) $(Cflags) -lm eratosthenes.o error.o primes.c -o primes
	$(CC) $(Cflags) -lm -DUSE_INLINE eratosthenes.o error.o primes.c -o primes-i

steg:

eratosthenes.o:
	$(CC) $(Cflags) -c eratosthenes.c

error.o: error.c
	$(CC) $(Cflags) -c error.c

clean:
	rm *.o primes primes-i