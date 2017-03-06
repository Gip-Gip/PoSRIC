/* p_addDr.h - includes files needed by p_addDr.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_ADDDR_H
#include <p_messag.h>
#include <p_dir.h>

#define P_FREEALL() if(in) {fclose(in);in = NULL;} \
                    if(tmp) {fclose(tmp);tmp = NULL;} \
                    P_FTREM(FUNCNAME); P_DTDINIT(p_getRdgDT); \
                    ssln_rid(currTime);

#define P_ADDDR_H_H NULL
#endif
