/* p_help.h - includes files and defines things needed by p_help.c

ENUMS:

TYPEDEFS:

DEFINITIONS:

HELP_USAGE - a message that describes the usage of ARay
HELP_FORMAT - the p_print format for each command line argument

MACROS:

*/

#ifndef P_HELP_H
#include <p_common.h>
#include <p_args.h>
#include <p_messag.h>

#define HELP_USAGE "\nUSAGE:\n\n%s [arguments]\n\n\
arguments are read left to right\n\n", PROGNAME
#define HELP_FORMAT "\"%s\" or \"%s\" %s\n", \
                    p_args[index + ARGS_SHRTDPTH], \
                    p_args[index + ARGS_LONGDPTH], \
                    p_args[index + ARGS_HELPDPTH]

#define P_HELP_H NULL
#endif
