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

//TODO make multiple uses of macros in one program possible
#ifndef _BITSET_H
#define _BITSET_H

#include <stdlib.h>
#include <limits.h> // used for CHAR_BITS
#include <assert.h>

#include "error.h"

#define _BITS_IN_LONG (sizeof(unsigned long) * CHAR_BIT)
#define _MAX_LSHIFT _BITS_IN_LONG - 1

typedef unsigned long int * bitset_t;
typedef unsigned long int bitset_index_t;

/**
 * @brief create a bitset called name with size size + 1, to store the size
 * the first index will store the size of the bitfield
 * initializes the bitfield with zeroes and stores size in the 0th index
 */
#define bitset_create(name, size)\
    static_assert(size > 0);\
    unsigned long int _true_size = (size) + 1;\
    unsigned long int name[_true_size];\
    name[0] = (size);\
    for (size_t i = 1; i < _true_size; i++) name[i] = 0;


/**
 * @brief create a dynamicaly allocated bitset 
 * called name with size size + 1, to store the size
 * initializes the bitfield with zeroes and stores size in the 0th index
 */
#define bitset_alloc(name, size)\
    static_assert(size > 0);\
    unsigned long _true_size = (size) + 1;\
    bitset_t name = malloc(sizeof(unsigned long) * _true_size);\
    name[0] = (size);\
    for (size_t i = 1; i < _true_size; i++) name[i] = 0;

/**
 * @brief free bitset created with bitset_alloc
 * 
 */
#define bitset_free(name)\
    free(name);

/**
 * @brief return size of the bitset "name"
 * 
 */
#define bitset_size(name)\
    name[0]

/**
 * @brief sets bit on index "index" to either 1 or 0
 * depending on what "expr" evaluates to
 * 
 * first it checks if index is valid (not out of bitset)
 */
#define bitset_setbit(name, index, expr)\
    bitset_index_t _index_max = _BITS_IN_LONG * bitset_size(name);\
    if ((index) > _index_max) error_exit("Index: %lu is higher than max index: (%lu)\n", (unsigned long) (index), (unsigned long) _index_max);\
    bitset_index_t _index_real = (index) / _BITS_IN_LONG + 1;\
    unsigned int _index_offset = _MAX_LSHIFT - (index) % _BITS_IN_LONG;\
    if (expr) name[_index_real] |= 1ul << _index_offset;\
    else name[_index_real] &= ~(1ul << _index_offset - 1);

/**
 * @brief returns value bit in "name" on "index"
 * //TODO check boundries of the bitset
 */
#define bitset_getbit(name, index)\
    (name[(index)/_BITS_IN_LONG +1] & 1ul << (_MAX_LSHIFT - ((index) % _BITS_IN_LONG))) ? 1 : 0

#endif //_BITSET_H\ No newline at end of file