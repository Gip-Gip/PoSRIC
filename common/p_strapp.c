/* p_strapp - combines the base and source string

ARGUMENTS:

string base - the base string
string source - the string being appended to the base
bool freeBase - free the base
bool freeSource - free the source

VARIABLES:

string out - the string being returned

*/

#include <p_strapp.h>

string p_strapp(string base, string source, bool freeBase, bool freeSource)
{
    string out = calloc(strlen(base) + strlen(source) + STRALLOC,
                        sizeof(character));

    strcpy(out, base);
    strcat(out, source);

    if(freeBase) free(base);
    if(freeSource) free(source);

    return out;
}
