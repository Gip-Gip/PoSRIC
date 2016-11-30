/* p_getStr - get a string from the given file

ARGUMENTS:

FILE *in - the file being read
character term - the character which signal to stop reading

VARIABLES:

string buffer - the string being created/returned
character prebuff[] - the pre-buffer buffer
bool ridWS - if set, whitespace will be ignored

*/

#include <p_getStr.h>

string p_getStr(FILE *in, character term, bool ridWS)
{
    string buffer = calloc(STRALLOC, sizeof(character));
    character prebuff[] = {0, 0};

    for(*prebuff = fgetc(in);
        !feof(in) && *prebuff != term;
        *prebuff = fgetc(in))

        if(!ridWS || !isspace(*prebuff))
            buffer = p_strapp(buffer, prebuff, true, false);

    return buffer;
}
