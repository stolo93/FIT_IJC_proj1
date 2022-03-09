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

    for (bitset_index_t i = 3; i <= pole[0]; i+=2)
    {
        for (bitset_index_t j = i * i; j <= pole[0] && !bitset_getbit(pole, i); j += i)
        {
            bitset_setbit(pole, j, 1);
        }
    }

    bitset_index_t count = 0;

    for (bitset_index_t i = (pole[0] % 2 ? pole[0] : pole[0] -1); i >=2; i-=2)
    {   
        if ((i%2) == 0)
        {   
            continue;
        }
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
    if (count == 9)
    {
        printf("%lu\n", 2);
    }

    return;
}