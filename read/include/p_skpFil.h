/* p_skpFil.h - included files needed by p_skpFil.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_SKPFIL_H

#include <p_common.h>

extern rType p_fileRdgs[];

#define P_FREEALL() {p_dontRecDir = false; if(buffer) free(buffer);}

#define P_SKPFIL_H NULL
#endif
