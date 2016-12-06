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
                    if(params) free(params); \
                    if(comm) free(comm); \
                    if(p_stdin != stdin) fclose(p_stdin); \
                    if(logFile) fclose(logFile);


#define MAIN_H NULL
#endif
