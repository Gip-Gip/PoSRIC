/* p_rmDir.h - includes files needed by p_rmDir.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_RMDIR_H
#include <p_messag.h>
#include <p_dir.h>

#define P_FREEALL() if(tmp) {fclose(tmp);tmp = NULL;} \
                    if(in) {fclose(in);in = NULL;} \
                    P_FTREM(FUNCNAME); P_DTDINIT(p_getRdgDT);

#define P_RMDIR_H NULL
#endif
