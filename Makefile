CC=gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
CLIBS = -lm

all: primes steg-decode

run: all
	./primes && ./primes-i
	./steg-decode du1-obrazek.ppm

primes: error.o	eratosthenes.o primes.o
	$(CC) $(CFLAGS) $(CLIBS) $^ -o $@
	$(CC) $(CFLAGS) $(CLIBS) -DUSE_INLINE $^ -o $@-i

steg-decode: steg-decode.o ppm.o eratosthenes.o error.o
	$(CC) $(CFLAGS) $(CLIBS) $^ -o $@

%.o: %.c 
	$(CC) $(CFLAGS) -c $^

zip: *.c *.h Makefile
	$@ xstola03.$@ $^

clean:
	rm *.o primes primes-i steg-decode