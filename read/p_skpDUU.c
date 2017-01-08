/* p_skpDUU - skips data until the specified descriptor ridge is found, or
              returns an error if the brkridge is found

ARGUMENTS:

FILE *in - the file being skipped through
rType cmpridge - the ridge being searched for
rType brkridge - the ridge that breaks the search
bool seekBack - seeks back if set

VARIABLES:

rType cmpret - where the current ridge is stored; used to compare ridges
retVal ret2 - the secondary return variable
byte *ret - the primary return variable. Used to free the uneeded buffer
            returned by p_getRdg

*/

#include <p_skpDUU.h>

retVal p_skpDUU(FILE *in, rType cmpridge, rType brkridge, bool seekBack)
{
    rType cmpret;
    retVal ret2;
    byte *ret;

    P_FTADD(FUNCNAME);

    while((ret = p_getRdg(in, &cmpret)) &&  cmpret != cmpridge &&
            cmpret != brkridge && cmpret != rType_end)
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

    if(cmpret == rType_end) return err_rNotFound;

    if(seekBack) fseek(in, -P_RMINRD, SEEK_CUR);

    return none;
}
