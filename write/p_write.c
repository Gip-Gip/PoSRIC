/* p_write writes the given data to an archive

ARGUMENTS:

byte *data - the data being written
natural size - the size of the data
FILE *out - the archive being written to

VARIABLES:

retVal ret - used to store the return values of functions

*/

#include <p_write.h>

retVal p_write(byte *data, natural size, FILE *out)
{
    retVal ret;

    P_FTADD(FUNCNAME);

    for(;size / P_RMAXSZ; data += P_RMAXSZ, size -= P_RMAXSZ)
    {
        if((ret = p_wrtRdg(out, P_RMAXSZ, data)))
        {
            P_FREEALL();
            return ret;
        }
    }

    if(size && (ret = p_wrtRdg(out, size, data)))
    {
        P_FREEALL();
        return ret;
    }

    P_FREEALL();

    return none;
}
