/* p_getStr - get a string from the given file

ARGUMENTS:

FILE *in - the file being read
character term - the character which signal to stop reading
bool ridWs - set if you want to remove whitespace

VARIABLES:

string buffer - the string being created/returned
character prebuff[] - the pre-buffer buffer

*/

#include <p_getStr.h>

string p_getStr(FILE *in, character term, bool ridWS)
{
    string buffer = calloc(STRALLOC, sizeof(character));
    character prebuff[] = {0, 0};

    for(*prebuff = fgetc(in);
        !feof(in) && *prebuff != term;
        *prebuff = fgetc(in))
    {
        if(*prebuff == ESCDELEM) *prebuff = fgetc(in);

        if(!ridWS || !isspace(*prebuff))
            buffer = p_strapp(buffer, prebuff, true, false);
    }

    return buffer;
}
