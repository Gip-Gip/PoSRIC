/* p_skpDir - skips all the ridges that are found inside a file

ARGUMENTS:

FILE *in - the file being skipped through

VARIABLES:

*/

#include <p_skpDir.h>

retVal p_skpDir(FILE *in)
{
    byte *buffer;
    rType ridge;
    natural startCount = p_getRdgDT.dirCount;

    P_FTADD(FUNCNAME);

    while((buffer = p_getRdg(in, &ridge)) &&
          p_getRdgDT.dirCount >= startCount &&
          ridge != rType_end) free(buffer);

    if(!buffer)
    {
        P_FREEALL();
        return ridge;
    }

    P_FREEALL();

    return none;
}
