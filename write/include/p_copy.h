/* p_copy.h - includes files needed by p_copy.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_COPY_H
#include <p_common.h>

#define P_FREEALL() if(buffer) free(buffer); P_FTREM(FUNCNAME);

#define P_COPY_H NULL
#endif
