/**
 * @file error.c
 * @author Samuel Stolarik (xstola03@stud.fit.vutbr.cz)
 * @brief implementation of error handling functions from error.h
 * @version 0.1
 * @date 2022-03-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "headers/error.h"


void warning_msg(const char * format, ...)
{
    fprintf(stderr, "CHYBA: ");

    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    return;
}

void error_exit(const char * format, ...)
{
    fprintf(stderr, "CHYBA: ");

    va_list args;
    
    va_start(args,format);
    vprintf(args, format);
    va_end(args);

    exit(1);
}
