/**
 * @file error.c
 * @author Samuel Stolarik (xstola03@stud.fit.vutbr.cz), FIT
 * 
 * @brief IJC-DU1, part B
 * decoding hidden message in a ppm file
 * Used compiler: gcc (GCC) 11.2.0
 * 
 * @date 2022-03-03
 */

#include "ppm.h"
#include "error.h"
#include "bitset.h"

//--function prototypes--
extern void Eratosthenes(bitset_t pole)


int main(int argc, char ** argv)
{
    ppm_t * pic = ppm_read(argv[1]);
    
    bitset_alloc(primes, (pic -> xsize) * (pic -> ysize) * RGB_PARTS);
    
    ppm_free(pic);
    return 0;
}