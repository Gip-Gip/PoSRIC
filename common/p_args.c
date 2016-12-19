/*

ARGUMENTS:

VARIABLES:

string p_args[] - holds all the arguments

*/

#include <p_types.h>

string p_args[] =
{
    "-a", "--archive", "set the archive to be used",
    "-A", "--authors", "displays a list of authors",
    "-b", "--buffer-size", "sets the buffer size for writing",
    "-f", "--format", "formats the archive",
    "-h", "--help", "displays this message and exits",
    "-l", "--log", "sets the logfile",
    "-L", "--license", "displays the license and exits",
    "-n", "--no-script", "don't expect a script; only runs off of arguments",
    "-q", "--quick-add", "add a file with the native filename to the archive",
    "-Q", "--quick-get", "gets filedata from the archive",
    "-s", "--script", "sets the script file, and uses it in place of stdio.h",
    "-t", "--tmp-file", "sets the temporary file",
    "-v", "--verbose", "prints extra debugging messages",
    "-y", "--overwrite", "overwrites files without complaining",
    NULL,
};
