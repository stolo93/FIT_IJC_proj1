/**
 * @file eratosthenes.c
 * @author Samuel Stolarik (xstola03@stud.fit.vutbr.cz)
 * @brief eratosthenes algoritm for finding primes
 * @version 0.1
 * @date 2022-03-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>

#include "headers/bitset.h"
#include "headers/error.h"

void Eratosthenes(bitset_t pole)
{
    bitset_setbit(pole, 0, 1);  
    bitset_setbit(pole, 1, 1);

    for (bitset_index_t i = 2; i < pole[0] -1; i++)
    {
        if (bitset_getbit(pole, i))
        {
            continue; //skipping if number was already filtered out
        }
        for (bitset_index_t j = i * 2; j < pole[0]; j += i)
        {
            bitset_setbit(pole, j, 1);
        }
    }

    bitset_index_t count = 0;

    for (bitset_index_t i = pole[0] -1; i >=2; i--)
    {
        if (count == 10)
        {
            break;
        }

        if (!bitset_getbit(pole, i))
        {
            printf("%lu\n",i);
            count++;
        }
    }

    return;
}