CC=gcc
Cflags = -g -std=c11 -pedantic -Wall -Wextra

all: primes steg

run: all
	./primes && ./primes-i
	./steg-decode du1-obrazek.ppm

run_check: all
	time ./primes | factor && time ./primes-i | factor
	./steg-decode du1-obrazek.ppm
	rm *.o primes primes-i	steg-decode

primes: error.o	eratosthenes.o primes.o
	$(CC) $(Cflags) -lm eratosthenes.o error.o primes.o -o primes
	$(CC) $(Cflags) -lm -DUSE_INLINE eratosthenes.o error.o primes.o -o primes-i

steg: steg-decode.o ppm.o eratosthenes.o error.o
	$(CC) $(Cflags) -lm steg-decode.o ppm.o eratosthenes.o error.o -o steg-decode

primes.o: primes.c
	$(CC) $(Cflags) -c primes.c

eratosthenes.o: eratosthenes.c
	$(CC) $(Cflags) -c eratosthenes.c

error.o: error.c
	$(CC) $(Cflags) -c error.c

steg-decode.o: steg-decode.c
	$(CC) $(Cflags) -c steg-decode.c

ppm.o: ppm.c
	$(CC) $(Cflags) -c ppm.c

zip: *.c *.h Makefile
	zip xstola03.zip *.c *.h Makefile

clean:
	rm *.o primes primes-i steg-decode