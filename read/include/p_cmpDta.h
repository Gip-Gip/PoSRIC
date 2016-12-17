/* p_cmpDta.h - includes files needed by p_cmpDta.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_CMPDTA_H
#include <p_messag.h>

#define P_FREEALL() if(buffer) {free(buffer); buffer = NULL;} P_FTREM(FUNCNAME);

#define P_CMPDTA_H NULL
#endif
