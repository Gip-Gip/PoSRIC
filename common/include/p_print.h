/* p_print.h - includes files and defines things needed by p_print.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

PRINT_STYLDELM - the style delemeter
PRINT_STYLSTR - the style code for a string
PRINT_STYLNATR - the style code for a natural number
PRINT_STYLPREV - the style code for the previous string
PRINT_STYLVERB - the style code for marking verbose-only strings
PRINT_STYLCHAR - the style code for a single character
PRINT_NCORR - the amount to compensate due to the inaccuracy of number-length
              detection algorithms

MACROS:

LPUTC - prints a character to both the log file and stderror

*/

#ifndef P_PRINT_H
#include <p_messag.h>
#include <math.h>
#include <stdarg.h>

extern FILE *logFile;
extern bool verbose;

#define PRINT_STYLDELM '%'
#define PRINT_STYLSTR 's'
#define PRINT_STYLNATR 'n'
#define PRINT_STYLPREV '<'
#define PRINT_STYLNPREV '#'
#define PRINT_STYLVERB 'v'
#define PRINT_STYLCHAR 'c'
#define PRINT_NCORR 2
#define P_PRINT_H NULL
#endif
