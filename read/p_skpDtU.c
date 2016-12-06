/* p_skpDtU - skips data until the specified descriptor ridge is found

ARGUMENTS:

FILE *in - the file being skipped through
rtype ridge - the ridge being searched for

VARIABLES:

rtype cmpret - where the current ridge is stored; used to compare ridges
retval ret2 - the secondary return variable
byte *ret - the primary return variable. Used to free the uneeded buffer
            returned by p_getRdg

*/

#include <p_skpDtU.h>

retval p_skpDtU(FILE *in, rtype ridge)
{
    rtype cmpret;
    retval ret2;
    byte *ret;

    while((ret = p_getRdg(in, &cmpret)) &&  cmpret != ridge &&
            cmpret != rtype_end)
    {
        free(ret);

        if((ret2 = p_skpDta(in))) return ret2;
    }

    if(!ret) return cmpret;

    free(ret);

    fseek(in, -P_RMINRD, SEEK_CUR);

    return none;
}
