/* p_addFd.h - includes files needed by p_addFd.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_ADDFD_H
#include <p_messag.h>
#include <p_dir.h>

#define P_FREEALL() { if(tmp) {fclose(tmp);tmp = NULL;} \
                    if(in) {fclose(in);in = NULL;} \
                    if(dataFile) {fclose(dataFile);dataFile = NULL;} \
                    if(buffer) free(buffer); \
                    P_FTREM(FUNCNAME); P_DTDINIT(p_getRdgDT); }

#define P_ADDFD_H NULL
#endif
