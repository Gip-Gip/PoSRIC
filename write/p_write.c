/* p_write

ARGUMENTS:

VARIABLES:

*/

#include <p_write.h>

retval p_write(byte *data, natural size, FILE *out)
{
    natural fullWrites = size / P_DATA;
    retval ret;

    while(fullWrites --)
    {
        if((ret = p_wrtRdg(out, P_DATA, data)))
            return ret;

        data += P_DATA;
    }

    if(size % P_DATA && (ret = p_wrtRdg(out, size % P_DATA, data)))
        return ret;

    return none;
}
