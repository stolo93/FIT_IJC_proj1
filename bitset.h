/**
 * @file bitset.h
 * @author Samuel Stolarik (xstola03@fit.vutbr.cz), FIT
 * 
 * @brief IJC-DU1, part A
 * header file containing macros and inline functions
 * needed for operations on bitsets
 * 
 * @date 2022-03-01
 */

#ifndef _BITSET_H
#define _BITSET_H

#include <stdlib.h>
#include <limits.h> // used for CHAR_BIT
#include <assert.h> //used for static_assert
#include <stdbool.h>

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
    unsigned long int name[(size / _BITS_IN_LONG) + ((size % _BITS_IN_LONG) ? 1 : 0) + 1] = {[0] = (size), 0};\

/**
 * @brief create a dynamicaly allocated bitset 
 * called name with size size + 1, to store the size
 * initializes the bitfield with zeroes and stores size in the 0th index
 */
#define bitset_alloc(name, size)\
    static_assert(size > 0);\
    bitset_t name = calloc(((size / _BITS_IN_LONG) + ((size % _BITS_IN_LONG) ? 1 : 0) + 1), sizeof(unsigned long));\
    name[0] = (size);\

#ifndef USE_INLINE

/**
 * @brief free bitset created with bitset_alloc
 * 
 */
#define bitset_free(name)\
    free(name)

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
        if ((index) > (_BITS_IN_LONG * bitset_size(name))) error_exit("Index: %lu is higher than max index: (%lu)\n", (unsigned long) (index), (unsigned long) (_BITS_IN_LONG * bitset_size(name)));\
        else if (expr) name[(index) / _BITS_IN_LONG + 1] |= 1ul << (_MAX_LSHIFT - (index) % _BITS_IN_LONG);\
        else name[(index) / _BITS_IN_LONG + 1] &= ~1ul << (_MAX_LSHIFT - (index) % _BITS_IN_LONG)
    

/**
 * @brief returns value bit in "name" on "index"
 *
 */
#define bitset_getbit(name, index)\
    ((index > _BITS_IN_LONG * bitset_size(name)) ?\
    (error_exit("Index: %lu is higher than max index: (%lu)\n", (unsigned long) (index), (unsigned long)(_BITS_IN_LONG * bitset_size(name))),0):\
    ((name[(index)/_BITS_IN_LONG +1] & 1ul << (_MAX_LSHIFT - ((index) % _BITS_IN_LONG))) ? 1 : 0))

#else //USE_INLINE

//TODO are this functions even meaningfull  ?
// inline bitset_t bitset_create(/*TODO type*/ name, bitset_index_t size)
// {
// 
// }

// inline bitset_t bitset_alloc(/*TODO type*/ name, bitset_index_t size)
// {
// 
// }

/**
 * @brief free memmory allocated by bitset_alloc pointed to by "name"
 * 
 * @param name 
 */
extern inline void bitset_free(bitset_t name)
{
    free(name);
}

/**
 * @brief returns size of bitset
 * 
 * @param name 
 * @return bitset_index_t 
 */
extern inline bitset_index_t bitset_size(bitset_t name)
{
    return name[0];
}

/**
 * @brief sets bit at index "index" depending on what "expr evaluates to"
 * 
 * @param name 
 * @param index 
 * @param expr 
 */
extern inline void bitset_setbit(bitset_t name, bitset_index_t index, bool expr)
{
    bitset_index_t max_index = bitset_size(name) * _BITS_IN_LONG;
    bitset_index_t index_real = (index) / _BITS_IN_LONG + 1;
    unsigned int index_offset = _MAX_LSHIFT - (index) % _BITS_IN_LONG;

    if (index > max_index)
    {
        error_exit("Index: %lu is higher than the max index: %lu.\n", index, max_index);
    }

    if (expr)
    {
        name[index_real] |= 1ul << index_offset;
    }
    else
    {
        name[index_real] &= ~(1ul << index_offset - 1);
    }
    return;
}

/**
 * @brief returns bool value depending of value of bit on index "index"
 * 
 * @param name 
 * @param index 
 * @return true 
 * @return false 
 */
extern inline bool bitset_getbit(bitset_t name, bitset_index_t index)
{
    bitset_index_t max_index = _BITS_IN_LONG * bitset_size(name);
    if (index > max_index)
    {
        error_exit("Index: %lu is higher than max index: (%lu)\n",index, max_index);
    }
    else
    {
        return (name[(index)/_BITS_IN_LONG +1] & 1ul << (_MAX_LSHIFT - (index % _BITS_IN_LONG))) ? true : false;
    }
}

#endif //USE_INLINE
#endif //_BITSET_H\ No newline at end of file