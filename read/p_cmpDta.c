/* p_cmpdta - compares data to an archive

ARGUMENTS:

byte *data - the data being compared
natural size - the size of the data being compared
FILE *in - the archive being compared to the data
natural *bytesRead - where to store the total amount of bytes read

VARIABLES:

byte *buffer - used to compare

*/

#include <p_cmpDta.h>

bool p_cmpDta(byte *data, natural size, FILE *in, natural *bytesRead)
{
    byte *buffer;
    rtype ret;

    *bytesRead = ZERO;

    for(buffer = p_getRdg(in, &ret),
            *bytesRead += ((ret += P_RTYPECORR + P_DCORR) > P_DATA + P_DCORR ?
                ZERO : P_RMINRD + ret);

        !feof(in) && buffer && ret <= P_DATA + P_DCORR;

        buffer = p_getRdg(in, &ret),
            *bytesRead += ((ret += P_RTYPECORR + P_DCORR) > P_DATA + P_DCORR ?
                ZERO : P_RMINRD + ret))
    {
        if(ret > size || memcmp(data, buffer, ret))
        {
            free(buffer);
            fseek(in, -(*bytesRead), SEEK_CUR);
            return false;
        }

        free(buffer);
        data += ret;
        size -= ret;
    }

    free(buffer);

    if(ret > P_DATA + P_DCORR && !size)
    {
        fseek(in, -(*bytesRead + P_RMINRD), SEEK_CUR);
        return true;
    }

    if(errno) return neither;

    return false;
}

