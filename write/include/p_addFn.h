/* p_addFn.h - includes files needed by p_addFn.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_ADDFN_H
#include <p_messag.h>

#define P_FREEALL() if(tmp) {fclose(tmp);tmp = NULL; if(!overwrite && \
                        remove(tmpName)) { \
                            perror(MSG_PERROR);return errno;}} \
                    if(in) {fclose(in);in = NULL;}

#define P_ADDFN_H NULL
#endif
