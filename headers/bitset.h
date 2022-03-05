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

typedef unsigned long int * bitset_t;
typedef unsigned long int bitset_index_t;

/**
 * @brief create a bitset called name with size size
 * the first index will store the size of the bitfield
 *  initializes the bitfield with zeroes
 */
#define bitset_create(name, size) {\
\
}


/**
 * @brief //TODO finish the documentation
 * 
 */
#define bitset_alloc(name, size) {\
\
}

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

#endif //_BITSET_H