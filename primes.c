/**
 * @file error.c
 * @author Samuel Stolarik (xstola03@stud.fit.vutbr.cz), FIT
 * 
 * @brief IJC-DU1, part A
 * prints last 10 primes less than 300000000
 * uses Sieve of Eratosthenes implemented in eratosthenes.c
 * Used compiler: gcc (GCC) 11.2.0
 * 
 * @date 2022-03-03
 */

#include <stdio.h>
#include <time.h>

#include "bitset.h"
#include "error.h"
//300000000
#define CNT_PRIMES 300000000//primes less than 
#define PRT_PRIMES 10 //how many primes to print

//---prototypes---

static void print_primes(const bitset_t primes, int count);
extern void Eratosthenes(bitset_t array);


int main()
{
    clock_t start = clock();

    bitset_create(primes, CNT_PRIMES);

    Eratosthenes(primes);

    print_primes(primes, PRT_PRIMES);

    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}


/**
 * @brief print last "count" primes from bitset "primes"
 * if there is less then "count" primes, prints only as much as possible
 * 
 * @param primes 
 * @param count 
 */
static void print_primes(const bitset_t primes, int count)
{
    bitset_t primes_to_print = calloc(sizeof(unsigned long int), count);
    if (primes_to_print == NULL)
    {
        error_exit("Ran out of memory.");
    }

    short cur = count -1;

    for (bitset_index_t i = bitset_size(primes) -1; i >= 2; i--)
    {
        if (!bitset_getbit(primes, i) && cur >= 0)
        {
            primes_to_print[cur--] = i;
        }
    }
    
    for(short i = 0; i < count; i++)
    {
        if (primes_to_print[i])
        printf("%lu\n",primes_to_print[i]);
    }

    free(primes_to_print);

    return;
}
