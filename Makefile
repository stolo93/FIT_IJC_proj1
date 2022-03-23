CC=gcc
CFLAGS = -m32 -g -std=c11 -pedantic -Wall -Wextra
LDFLAGS = -lm
XLOG = xstola03

all: primes steg-decode

run: primes
	ulimit -s 50000 && ./primes
	ulimit -s 50000 && ./primes-i

primes: error.o	eratosthenes.o primes.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	$(CC) $(CFLAGS) -DUSE_INLINE $^ -o $@-i $(LDFLAGS)

steg-decode: steg-decode.o ppm.o eratosthenes.o error.o
	$(CC) $(CFLAGS)  $^ -o $@ $(LDFLAGS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $^

zip: *.c *.h Makefile
	$@ $(XLOG).$@ $^

clean:
	rm *.o primes primes-i steg-decode