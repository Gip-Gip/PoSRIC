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

string p_getStr(FILE *in, character term, character *usedTerm, bool ridWS)
{
    string buffer = calloc(STRALLOC, sizeof(character));
    character prebuff[] = {0, 0};

    while
    (

        (
            ((*prebuff = fgetc(in)) | ONE) &&
            !feof(in) &&
            *prebuff != term &&
            *prebuff != FULLTERM &&
            /* To allow DOS scripts to be run on UNIX machines, we have to
               recognize CR as it's own line terminator */
            *prebuff != DOSFULTERM
        ) ||
        !strlen(buffer)
    )
    {
        if(*prebuff == ESCDELEM) *prebuff = fgetc(in);

        if(!ridWS || !isspace(*prebuff))
            buffer = p_strapp(buffer, prebuff, true, false);
    }

    *usedTerm = *prebuff;

    return buffer;
}
