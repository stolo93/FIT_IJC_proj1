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
extern void Eratosthenes(bitset_t pole);


int main(int argc, char ** argv)
{   
    if (argc != 2)
        error_exit("No file given\n");
    
    ppm_t * pic = ppm_read(argv[1]);
    if (pic == NULL)
        error_exit("Problem with reading the file\n");

    unsigned long pic_size = pic -> xsize * pic -> ysize * RGB_PARTS;
    bitset_alloc(primes, pic_size);
    if (primes == NULL)
    {
        free(pic);
        error_exit("Ran out of space, while allocating for primes bitset.\n");
    }
    
    Eratosthenes(primes);

    unsigned msg_size = 100; //assumed size of the message
    char * message = calloc(msg_size, sizeof(char));
    if (message == NULL)
    {
        free(pic);
        bitset_free(primes);
        error_exit("Ran out of space while allocating space for message.\n");
    }

    unsigned stored_chars = 0;
    int bit_count = 0;

    for (bitset_index_t i = 29; i <= pic_size; i++){
        if (bitset_getbit(primes, i))
        {
            if (bit_count == 8)
            {
                bit_count = 0;
                stored_chars++;
            }
            if (stored_chars >= msg_size)   //reallocating message if it is longer than expected
            {
                msg_size *= 2;
                char * tmp = realloc(message, msg_size);
                if (tmp != NULL)
                {
                    message = tmp;
                }
                else
                {
                    free(message);
                    bitset_free(primes);
                    free(pic);
                    error_exit("Ran out of space while reallocating space for message.\n");
                }
            }
            char tmp = pic -> data[i] & 1u;
            message[stored_chars] |= (tmp << bit_count++);
        }
    }
    
    bitset_free(primes);

    for (unsigned i = 0; message[i]; i++)
    {
        putchar(message[i]);
    }
    
    free(message);
    ppm_free(pic);
    return 0;
}