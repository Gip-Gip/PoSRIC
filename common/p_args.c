/*

ARGUMENTS:

VARIABLES:

string p_args[] - holds all the arguments

*/

#include <p_types.h>

string p_args[] =
{
    "-h", "--help", "displays this message and exits",
    "-l", "--log", "sets the logfile",
    "-L", "--license", "displays the license and exits",
    "-v", "--verbose", "p_print extra debugging messages",
    "-y", "--overwrite", "overwrites files without complaining",
    NULL,
};
