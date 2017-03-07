/* p_ut2lt.h - includes files needed by p_t2ut.h

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_UT2LT_H
#include <p_dir.h>
#include <p_messag.h>

#define P_FREEALL() { if(buffer) free(buffer); \
                    if(in)fclose(in); P_FTREM(FUNCNAME); P_DTDINIT(p_getRdgDT);\
                    ssln_rid(cTime);}

#define P_UT2LT_H NULL
#endif
