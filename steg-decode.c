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

#include <stdio.h>
#include <stdlib.h>

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
        warning_msg("Ran out of space, while allocating for primes bitset.\n");
        goto error_handling1;
    }
    
    Eratosthenes(primes);

    unsigned msg_size = 100; //assumed size of the message
    char * message = calloc(msg_size, sizeof(char));
    if (message == NULL)
    {
        warning_msg("Ran out of space while allocating space for message.\n");
        goto error_handling2;
    }

    unsigned stored_chars = 0;
    int bit_count = 0;

    for (bitset_index_t i = 29; i <= pic_size; i++){
        if (!bitset_getbit(primes, i))
        {
            if (bit_count == 8)
            {
                if (message[stored_chars] == '\0') break;   //finish reading if '\000' has been read
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
                    warning_msg("Ran out of space while reallocating space for message.\n");
                    goto error_handling3;
                }
            }
            //part that stores single bits into bytes
            char tmp = pic -> data[i] & 1u;
            message[stored_chars] |= (tmp << bit_count++);
        }
    }

    message = realloc(message, stored_chars); //shrinking the message size according to number of stored chars
    printf("stored chars: %u\n", stored_chars);
    for (unsigned i = 0; message[i]; i++)
    {
        putchar(message[i]);
    }

    error_handling3:
    free(message);
    error_handling2:
    bitset_free(primes);    
    error_handling1:
    ppm_free(pic);
    return 0;
}