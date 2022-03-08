/**
 * @file error.h
 * @author Samuel Stolarik (xstola03@fit.vutbr.cz)
 * @brief error handling header file
 * @version 0.1
 * @date 2022-03-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef _ERROR_H
#define _ERROR_H

#include <stdarg.h>
#include <stdio.h>
#include <stdnoreturn.h>

void warning_msg(const char *fmt, ...);

_Noreturn void error_exit(const char *fmt, ...);

#endif //_error_h