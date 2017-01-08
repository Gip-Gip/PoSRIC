/* p_skpDtU - skips data until the specified descriptor ridge is found

ARGUMENTS:

FILE *in - the file being skipped through
rType ridge - the ridge being searched for
bool seekBack - if set p_skpDtU will seek back 3 bytes

VARIABLES:

rType cmpret - where the current ridge is stored; used to compare ridges
retVal ret2 - the secondary return variable
byte *ret - the primary return variable. Used to free the uneeded buffer
            returned by p_getRdg

*/

#include <p_skpDtU.h>

retVal p_skpDtU(FILE *in, rType ridge, bool seekBack)
{
    rType cmpret;
    retVal ret2;
    byte *ret;

    P_FTADD(FUNCNAME);

    while((ret = p_getRdg(in, &cmpret)) &&  cmpret != ridge &&
            cmpret != rType_end)
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

    P_FREEALL();

    if(cmpret == rType_end) return err_rNotFound;

    if(seekBack) fseek(in, -P_RMINRD, SEEK_CUR);

    return none;
}
