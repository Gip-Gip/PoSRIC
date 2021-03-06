/* main.h - includes files needed by main.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef MAIN_H
#include <p_messag.h>
#include <p_prearg.h>
#include <p_dir.h>

#define P_FREEALL() if(tmpName && !argTmp) free(tmpName); \
                    if(name && !argName) free(name); \
                    if(params) free(params); \
                    if(comm) free(comm); \
                    if(p_stdin != stdin) {fclose(p_stdin);p_stdin = stdin;} \
                    if(logFile) {fclose(logFile);logFile = NULL;} \
/* P_DTDINIT automatically frees the archive name, so no need to include it
   here... */ \
                    P_FTDINIT(); P_DTDINIT(currDir);

#define MAIN_H NULL
#endif
