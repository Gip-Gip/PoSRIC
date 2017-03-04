/* p_list.h - includes files needed by p_list.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_LIST_H
#include <p_dir.h>
#include <p_messag.h>

#define P_FREEALL() { if(buffer) free(buffer); if(buffer2) free(buffer2); \
                    if(in)fclose(in); P_FTREM(FUNCNAME); P_DTDINIT(p_getRdgDT);\
                    ssln_rid(cTime);}

#define P_LIST_H NULL
#endif
