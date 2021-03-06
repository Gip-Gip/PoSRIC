/* strcut - cut a string from the source

ARGUMENTS:

string source - the string being cut from
natural amount -the amount of the string to cut out
bool freeSource - whether to free the source or not

VARIABLES:

string out - the string being returned

*/

#include <p_strcut.h>

string p_strcut(string source, natural amount, bool freeSource)
{
    string out = calloc(amount + STRALLOC, sizeof(character));

    memcpy(out, source, amount);

    if(freeSource) free(source);

    return out;
}
