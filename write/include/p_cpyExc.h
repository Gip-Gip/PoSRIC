/* p_cpyExc.h - includes files needed by p_cpyExc.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_CPYEXC_H_H
#include <p_messag.h>
#include <p_string.h>

#define P_FREEALL() if(buffer) free(buffer); P_FTREM(FUNCNAME);

#define P_CPYEXC_H NULL
#endif
