/* p_skpDtI - seeks through the file until a descriptor ridge is found that is
              not equal to the given cmpridge

ARGUMENTS:

FILE *in - the file being seeked through
rtype cmpridge - the ridge being compared to
bool seekBack - if set, p_skpDta seeks back 3 bytes

VARIABLES:

rtype ridge - used to get the value of the ridge
byte *ret - used to free the unused buffer generated by p_getRdg

*/

#include <p_skpDtI.h>

retval p_skpDtI(FILE *in, rtype cmpridge, bool seekBack)
{
    rtype ridge;
    byte *ret;

    P_FTADD(FUNCNAME);

    while((ret = p_getRdg(in, &ridge)) &&
        ((ridge + P_RTYPECORR) <= P_DATA || ridge == cmpridge) &&
        !feof(in))

        free(ret);

    if(!ret)
    {
        P_FREEALL();
        return err_unknown;
    }

    P_FREEALL();

    if(seekBack) fseek(in, -P_RMINRD, SEEK_CUR);

    return none;
}
