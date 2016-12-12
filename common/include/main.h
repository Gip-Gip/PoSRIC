/* main.h - includes files needed by main.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef MAIN_H
#include <p_messag.h>

#define P_FREEALL() if(tmpName) free(tmpName); \
                    if(archiveName) free(archiveName); \
                    if(name) free(name); \
                    if(params) free(params); \
                    if(comm) free(comm); \
                    if(p_stdin != stdin) {fclose(p_stdin);p_stdin = stdin;} \
                    if(logFile) {fclose(logFile);logFile = NULL;} \
                    P_FTDINIT();


#define MAIN_H NULL
#endif
