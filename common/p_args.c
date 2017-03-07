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
    "-da", "--add-dir", "adds a directory to the archive used",
    "-de", "--exit-dir", "exits the previous directory specified",
    "-dr", "--remove-dir", "removes the given directory in the archive used",
    "-du", "--use-dir", "uses the directory specified",
    "-f", "--format", "formats the archive",
    "-g", "--gui", "use the gui",
    "-h", "--help", "displays this message and exits",
    "-l", "--log", "sets the logfile",
    "-L", "--license", "displays the license and exits",
    "-n", "--no-script", "don't expect a script; only runs off of arguments",
    "-qa", "--quick-add", "add a file with the native filename to the archive",
    "-qg", "--quick-get", "gets filedata from the archive",
    "-qr", "--quick-remove", "removes a file from the archive",
    "-s", "--script", "sets the script file, and uses it in place of stdin",
    "-S", "--list", "lists the contents of the set archive",
    "-t", "--tmp-file", "sets the temporary file",
    "-T", "--stat", "displays the different properties of an in-archive file",
    "-v", "--verbose", "prints extra debugging messages",
    "-y", "--overwrite", "overwrites files without complaining",
    NULL,
};
