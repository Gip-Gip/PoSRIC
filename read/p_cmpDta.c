/* p_cmpdta - compares data to an archive

ARGUMENTS:

byte *data - the data being compared
natural size - the size of the data being compared
FILE *in - the archive being compared to the data

VARIABLES:

byte *buffer - used to compare

*/

#include <p_cmpDta.h>

bool p_cmpDta(byte *data, natural size, FILE *in)
{
    natural bytesRead = ZERO;
    byte *buffer;
    rtype ret;

    P_FTADD(FUNCNAME);

    for(buffer = p_getRdg(in, &ret),
            bytesRead += ((ret += P_RTYPECORR + P_DCORR) > P_DATA + P_DCORR ?
                ZERO : P_RMINRD + ret);

        !feof(in) && buffer && ret <= P_DATA + P_DCORR;

        buffer = p_getRdg(in, &ret),
            bytesRead += ((ret += P_RTYPECORR + P_DCORR) > P_DATA + P_DCORR ?
                ZERO : P_RMINRD + ret))
    {
        if(ret > size || memcmp(data, buffer, ret))
        {
            P_FREEALL();
            fseek(in, -bytesRead, SEEK_CUR);
            return false;
        }

        free(buffer);
        data += ret;
        size -= ret;
    }

    if(!buffer)
    {
        P_FREEALL();
        return neither;
    }

    P_FREEALL();

    if(ret > P_DATA + P_DCORR && !size)
    {
        fseek(in, -(bytesRead + P_RMINRD), SEEK_CUR);
        return true;
    }

    return false;
}


