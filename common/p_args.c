/*

ARGUMENTS:

VARIABLES:

string p_args[] - holds all the arguments

*/

#include <p_types.h>

string p_args[] =
{
    "-a", "--archive", "set the archive to be used",
    "-ad", "--add-dir", "adds a directory to the archive used",
    "-A", "--authors", "displays a list of authors",
    "-b", "--buffer-size", "sets the buffer size for writing",
    "-f", "--format", "formats the archive",
    "-h", "--help", "displays this message and exits",
    "-l", "--log", "sets the logfile",
    "-L", "--license", "displays the license and exits",
    "-n", "--no-script", "don't expect a script; only runs off of arguments",
    "-qa", "--quick-add", "add a file with the native filename to the archive",
    "-qg", "--quick-get", "gets filedata from the archive",
    "-qr", "--quick-remove", "removes a file from the archive",
    "-s", "--script", "sets the script file, and uses it in place of stdio.h",
    "-S", "--list", "lists the contents of the set archive",
    "-t", "--tmp-file", "sets the temporary file",
    "-u", "--use-dir", "uses the directory specified",
    "-U", "--exit-dir", "exits the previous directory specified",
    "-v", "--verbose", "prints extra debugging messages",
    "-y", "--overwrite", "overwrites files without complaining",
    NULL,
};
