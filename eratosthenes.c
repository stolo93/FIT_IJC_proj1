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
#define ODD_NUMS_64 0xAAAAAAAAAAAAAAAAul
#define ODD_NUMS_32 0xAAAAAAAAul

#include <stdio.h>
#include <math.h>

#include "bitset.h"

void Eratosthenes(bitset_t array)
{
    
    unsigned long odd_nums;
    bitset_index_t array_size = bitset_size(array) / BITS_IN_LONG + ((bitset_size(array) % BITS_IN_LONG) ? 1 : 0);
    
    //set the correct number depending on unsigned long being 4 or 8 bytes

    if (sizeof(unsigned long) == 8) odd_nums = ODD_NUMS_64;
    else odd_nums = ODD_NUMS_32;

    //filter out all odd numbers
    for (bitset_index_t i = 1; i < array_size + 1; i++)
    {
        array[i] = odd_nums;
    }
    

    bitset_setbit(array, 1, 1);
    bitset_setbit(array, 2, 0);

    unsigned long limit = (unsigned long) ceil(sqrt((double)bitset_size(array)));
 
    for (bitset_index_t i = 3; i < limit ; i+=2)
    {   
        if (bitset_getbit(array, i)) continue;
 
        for (bitset_index_t j = i*i; j < bitset_size(array); j+=i)
        {
            bitset_setbit(array, j, 1);
        }
    }
    return;
}