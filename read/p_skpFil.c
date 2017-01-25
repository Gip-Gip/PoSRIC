/* p_skpFil - skips all the ridges that are found inside a file

ARGUMENTS:

FILE *in - the file being skipped through
bool seekBack - if set, p_skpFil will seek back one ridge

VARIABLES:

*/

#include <p_skpFil.h>

retVal p_skpFil(FILE *in, bool seekBack)
{
    byte *buffer;
    rType ridge;

    P_FTADD(FUNCNAME); p_dontRecDir = true;

    while((buffer = p_getRdg(in, &ridge)) &&
          (ridge + P_RTYPECORR > P_DATA ? p_msCrAa(ridge, p_fileRdgs) : true))
            free(buffer);

    if(!buffer)
    {
        P_FREEALL();
        return ridge;
    }

    if(seekBack) fseek(in, -P_RMINRD, SEEK_CUR);

    P_FREEALL();

    return none;
}
