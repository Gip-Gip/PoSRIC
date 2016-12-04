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

    while((ret = p_getRdg(in, &ridge)) &&
        ridge + P_RTYPECORR <= P_DATA &&
        !feof(in) && !ferror(in))

        free(ret);

    if(!ret) return errno;

    free(ret);

    fseek(in, -P_RMINRD, SEEK_CUR);

    return none;
}
