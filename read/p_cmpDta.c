/* p_cmpdta - compares data to an archive's data

ARGUMENTS:

byte *data - the data being compared
natural size - the size of the data being compared
FILE *in - the archive being compared to the data

VARIABLES:

natural bytesRead - keeps track of the total amount of bytes read so p_cmpDta
                    can seek back
byte *buffer - used to compare the data and the archive's data
rtype ridge - the general ridge variable

*/

#include <p_cmpDta.h>

bool p_cmpDta(byte *data, natural size, FILE *in)
{
    natural bytesRead = ZERO;
    byte *buffer;
    rtype ridge;

    P_FTADD(FUNCNAME);

    for(buffer = p_getRdg(in, &ridge),
            bytesRead += ((ridge += P_RTYPECORR + P_DCORR) > P_DATA + P_DCORR ?
                ZERO : P_RMINRD + ridge);

        !feof(in) && buffer && ridge <= P_DATA + P_DCORR;

        buffer = p_getRdg(in, &ridge),
            bytesRead += ((ridge += P_RTYPECORR + P_DCORR) > P_DATA + P_DCORR ?
                ZERO : P_RMINRD + ridge))
    {
        if(ridge > size || memcmp(data, buffer, ridge))
        {
            P_FREEALL();
            fseek(in, -bytesRead, SEEK_CUR);
            return false;
        }

        free(buffer);
        data += ridge;
        size -= ridge;
    }

    if(!buffer)
    {
        P_FREEALL();
        return neither;
    }

    P_FREEALL();

    if(ridge > P_DATA + P_DCORR && !size)
    {
        fseek(in, -(bytesRead + P_RMINRD), SEEK_CUR);
        return true;
    }

    return false;
}


