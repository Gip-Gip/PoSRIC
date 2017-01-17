/* p_addFn.h - includes files needed by p_addFn.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_ADDFN_H
#include <p_messag.h>
#include <p_dir.h>

#define P_FREEALL() if(in) {fclose(in);in = NULL;} \
                    if(tmp) {fclose(tmp);tmp = NULL;} \
                    P_FTREM(FUNCNAME); P_DTDINIT(p_getRdgDT);

#define P_ADDFN_H NULL
#endif
