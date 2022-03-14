/**
 * @file eratosthenes.c
 * @author Samuel Stolarik (xstola03@stud.fit.vutbr.cz), FIT
 * 
 * @brief IJC-DU1, part A
 * implementing Sieve of Eratosthenes
 * Used compiler: gcc (GCC) 11.2.0
 * 
 * @date 2022-03-08
 */

#include <stdio.h>
#include <math.h>

#include "bitset.h"

void Eratosthenes(bitset_t array)
{
    bitset_setbit(array, 0, 1); 
    bitset_setbit(array, 1, 1);

    for (bitset_index_t i = 2; i <= sqrt(bitset_size(array)); i++)
    {   
        for (bitset_index_t j = i*i; j <= bitset_size(array) && !bitset_getbit(array, i); j+=i)
        {
            bitset_setbit(array, j, 1);
        }
    }
    return;
}