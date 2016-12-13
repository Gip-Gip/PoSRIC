/*

ARGUMENTS:

VARIABLES:

string p_args[] - holds all the arguments

*/

#include <p_types.h>

string p_args[] =
{
    "-a", "--authors", "displays a list of authors",
    "-b", "--buffer-size", "sets the buffer size for writing",
    "-h", "--help", "displays this message and exits",
    "-l", "--log", "sets the logfile",
    "-L", "--license", "displays the license and exits",
    "-s", "--script", "sets the script file, and uses it in place of stdio.h",
    "-v", "--verbose", "prints extra debugging messages",
    "-y", "--overwrite", "overwrites files without complaining",
    NULL,
};
