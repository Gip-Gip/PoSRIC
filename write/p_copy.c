/* p_copy - copys an archive to another

ARGUMENTS:

FILE *in - the file being read
FILE *out - the file being written to

VARIABLES:

*/

#include <p_copy.h>

retVal p_copy(FILE *in, FILE *out)
{
    byte *buffer;
    rType ridge;

    P_FTADD(FUNCNAME);

    for(;(buffer = p_getRdg(in, &ridge)) &&
        ridge != rType_end; free(buffer))
    {
        if(ridge + P_RTYPECORR > P_DATA) p_wrtRdg(out, ridge, NULL);

        else p_wrtRdg(out, ridge + P_RTYPECORR + P_DCORR, buffer);
    }

    P_FREEALL();

    if(!buffer) return ridge;

    return none;
}
