# School asignment for IJC class

Main language: C

## Main programs:

### primes.c

prints out last 10 prime numbers less than 300 000 000
for which it uses the Sieve of Eratosthenes
build generates two files:
* primes - uses macros for operations on bitsets
* primes-i uses inline functions for the same thing

### steg-decode.c

prints secret message hidden in du1-obrazek.ppm
* secret message is hidden at LS bits of bytes located at prime number indexes (starting with 29)
* every eight LSB make up to one byte of the secret starting with LSB

#### Build

Usage:
* make to build all executable files
* make run to build and run primes and primes-i
* make zip to create a zip (just for the assignement)
* make clean to clean all build files

Try running:
> make && ./steg-decode du1-obrazek.ppm

to reveal the secret message hidden in the picture