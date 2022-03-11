/**
 * @file error.h
 * @author Samuel Stolarik (xstola03@fit.vutbr.cz), FIT
 * 
 * @brief IJC-DU1, part B 
 * header file containing definitions of functions
 * used for handling errors
 * functions are implemented in error.c
 * 
 * @date 2022-03-01
 */


#ifndef _ERROR_H
#define _ERROR_H

#include <stdarg.h>
#include <stdio.h>
#include <stdnoreturn.h>

/**
 * @brief function prints error warning
 * warning starts with "CHYBA:" and contionus by fmt message
 * 
 * @param fmt 
 * @param ... 
 */
void warning_msg(const char *fmt, ...);

/**
 * @brief funciton prints error warning and calls exit(1)
 * warning start with "CHYBA:" and continus by fmt messege
 * 
 * @param fmt 
 * @param ... 
 * @return _Noreturn 
 */
_Noreturn void error_exit(const char *fmt, ...);

#endif //_error_h