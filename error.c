/**
 * @file error.c
 * @author Samuel Stolarik (xstola03@stud.fit.vutbr.cz), FIT
 * 
 * @brief IJC-DU1, part B
 * implementation of functions defined in error.h header file
 * Used compiler: gcc (GCC) 11.2.0
 * 
 * @date 2022-03-03
 */

#include "error.h"
#include <stdio.h>
#include <stdlib.h>

void warning_msg(const char *fmt, ...)
{
    fprintf(stderr, "CHYBA: ");

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    return;
}

_Noreturn void error_exit(const char *fmt, ...)
{
    fprintf(stderr, "CHYBA: ");

    va_list args;
    
    va_start(args,fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    exit(1);
}
