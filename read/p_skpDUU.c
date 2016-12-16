/* p_skpDUU - skips data until the specified descriptor ridge is found, or
              returns an error if the brkridge is found

ARGUMENTS:

FILE *in - the file being skipped through
rtype cmpridge - the ridge being searched for
rtype brkridge - the ridge that breaks the search
bool seekBack - seeks back if set

VARIABLES:

rtype cmpret - where the current ridge is stored; used to compare ridges
retval ret2 - the secondary return variable
byte *ret - the primary return variable. Used to free the uneeded buffer
            returned by p_getRdg

*/

#include <p_skpDUU.h>

retval p_skpDUU(FILE *in, rtype cmpridge, rtype brkridge, bool seekBack)
{
    rtype cmpret;
    retval ret2;
    byte *ret;

    P_FTADD(FUNCNAME);

    while((ret = p_getRdg(in, &cmpret)) &&  cmpret != cmpridge &&
            cmpret != brkridge && cmpret != rtype_end)
    {
        free(ret);

        if((ret2 = p_skpDta(in, true)))
        {
            P_FREEALL();
            return ret2;
        }
    }

    if(!ret)
    {
        P_FREEALL();
        return cmpret;
    }

    if(cmpret == brkridge)
    {
        P_FREEALL();
        return err_brkRidge;
    }

    P_FREEALL();

    if(cmpret == rtype_end) return err_rNotFound;

    if(seekBack) fseek(in, -P_RMINRD, SEEK_CUR);

    return none;
}
