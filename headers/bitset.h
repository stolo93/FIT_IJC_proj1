@@ -1,68 +0,0 @@ 
/**
 * @file bitset.h
 * @author Samuel Stolarik (xstola03@fit.vutbr.cz)
 * @brief header file with operations on a bitfield data structure
 * @version 0.1
 * @date 2022-03-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _BITSET_H
#define _BITSET_H

#include <stdlib.h>

typedef unsigned long int * bitset_t;
typedef unsigned long int bitset_index_t;

/**
 * @brief create a bitset called name with size size + 1, to store the size
 * the first index will store the size of the bitfield
 * initializes the bitfield with zeroes and stores size in the 0th index
 */
#define bitset_create(name, size) ({\
    static_assert(size > 0);\
    unsigned long int name[size + 1];\
    name[0] = size;\
    for (size_t i = 0; i < size; i++)\
    {\
        name[i + 1] = 0;\
    }\
})


/**
 * @brief create a dynamicaly allocated bitset 
 * called name with size size + 1, to store the size
 * initializes the bitfield with zeroes and stores size in the 0th index
 * 
 */
#define bitset_alloc(name, size) ({\
    static_assert(size > 0)\
    name = malloc(sizeof(unsigned long) * (size + 1));\
    name[0] = size;\
    for (size_t i = 0; i < size; i++)\
    {\
        name[i + 1] = 0;\
    }\
})

#define bitset_free(name) {\
\
}

#define bitset_size(name) {\
\
}

#define bitset_setbit(name, index, expr){\
\
}

#define bitset_getbit(name, index){\
\
}

#endif //_BITSET_H\ No newline at end of file