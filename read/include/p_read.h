/* p_read.h - includes files needed by p_read.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_READ_H

#include <p_messag.h>

#define P_FREEALL() if(preBuff) free(preBuff); if(buffer) free(buffer); \
                    P_FTREM(FUNCNAME);

#define P_READ_H NULL
#endif
