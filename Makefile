CC=gcc
Cflags = -g -std=c11 -pedantic -Wall -Wextra

all: primes steg

run: all
	./primes && ./primes-i

run_check: all
	time ./primes | factor && time ./primes-i | factor
	rm *.o primes primes-i	

primes: error.o	eratosthenes.o primes.o
	$(CC) $(Cflags) -lm eratosthenes.o error.o primes.o -o primes
	$(CC) $(Cflags) -lm -DUSE_INLINE eratosthenes.o error.o primes.o -o primes-i

steg:

primes.o: primes.c
	$(CC) $(Cflags) -c primes.c

eratosthenes.o: eratosthenes.c
	$(CC) $(Cflags) -c eratosthenes.c

error.o: error.c
	$(CC) $(Cflags) -c error.c

clean:
	rm *.o primes primes-i