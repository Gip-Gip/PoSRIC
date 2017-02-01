/* p_getFd.h - includes files needed by p_getFd.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_GETFD_H
#include <p_dir.h>
#include <p_messag.h>

#define P_FREEALL() {if(in) fclose(in); if(out) fclose(out); \
                    if(buffer) free(buffer); P_FTREM(FUNCNAME); \
                    P_DTDINIT(p_getRdgDT);}
#define P_GETFD_H NULL
#endif
