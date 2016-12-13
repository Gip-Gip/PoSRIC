/* p_format.h - includes files needed by p_format.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_FORMAT_H

#include <p_common.h>
#include <p_messag.h>
#include <p_string.h>

#define P_FREEALL() if(outFile) {fclose(outFile);outFile = NULL;} \
                    P_FTREM(FUNCNAME);

extern byte p_sig[P_SIGSZ];

#define P_FORMAT_H NULL
#endif
