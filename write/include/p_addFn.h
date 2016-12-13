/* p_addFn.h - includes files needed by p_addFn.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_ADDFN_H
#include <p_messag.h>

#define P_FREEALL() if(in) {fclose(in);in = NULL;} \
                    if(tmp) {fclose(tmp);tmp = NULL; if(overwrite && \
                        remove(tmpName)) {perror(MSG_PERROR);P_FTREM(FUNCNAME);\
                            return errno;}} \
                    P_FTREM(FUNCNAME);

#define P_ADDFN_H NULL
#endif
