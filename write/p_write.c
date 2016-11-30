/* p_write writes the given data to an archive

ARGUMENTS:

byte *data - the data being written
natural size - the size of the data
FILE *out - the archive being written to

VARIABLES:

retval ret - used to store the return values of functions

*/

#include <p_write.h>

retval p_write(byte *data, natural size, FILE *out)
{
    retval ret;

    for(;size / P_RMAXSZ; data += P_RMAXSZ, size -= P_RMAXSZ)
    {
        if((ret = p_wrtRdg(out, P_RMAXSZ, data)))
            return ret;
    }

    if(size && (ret = p_wrtRdg(out, size, data)))
        return ret;

    return none;
}
