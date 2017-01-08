/* p_rmFile.h - includes files needed by p_rmFile.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_RMFILE_H
#include <p_messag.h>
#include <p_dir.h>

#define P_FREEALL() if(tmp) {fclose(tmp);tmp = NULL;} \
                    if(in) {fclose(in);in = NULL;} \
                    P_FTREM(FUNCNAME); P_DTDINIT(p_getRdgDT);

#define P_RMFILE_H NULL
#endif
