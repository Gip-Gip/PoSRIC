/* p_skpDta - seeks through the file until a descriptor ridge is found

ARGUMENTS:

FILE *in - the file being seeked through

VARIABLES:

*/

#include <p_skpDta.h>

retval p_skpDta(FILE *in)
{
    rtype ridge;
    byte *ret;

    P_FTADD(FUNCNAME);

    while((ret = p_getRdg(in, &ridge)) &&
        ridge + P_RTYPECORR <= P_DATA &&
        !feof(in))

        free(ret);

    if(!ret)
    {
        P_FREEALL();
        return err_unknown;
    }

    P_FREEALL();

    fseek(in, -P_RMINRD, SEEK_CUR);

    return none;
}
