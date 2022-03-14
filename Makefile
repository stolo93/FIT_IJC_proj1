CC=gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
CLIBS = -lm
XLOG = xstola03

all: primes steg-decode

run: primes
	./primes
	./primes-i

primes: error.o	eratosthenes.o primes.o
	$(CC) $(CFLAGS) $(CLIBS) $^ -o $@
	$(CC) $(CFLAGS) $(CLIBS) -DUSE_INLINE $^ -o $@-i

steg-decode: steg-decode.o ppm.o eratosthenes.o error.o
	$(CC) $(CFLAGS) $(CLIBS) $^ -o $@

%.o: %.c 
	$(CC) $(CFLAGS) -c $^

zip: all *.c *.h Makefile
	$@ $(XLOG).$@ *.c *.h Makefile

clean:
	rm *.o primes primes-i steg-decode