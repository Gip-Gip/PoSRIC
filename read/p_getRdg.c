/* p_getRdg - gets the ridge from the specified file

ARGUMENTS:

FILE *in - the file being read
rtype *ret - the ridge value

VARIABLES:

rtype ridge - the ridge being read
fletcher checksum - the ridge checksum
byte *buffer - the buffer of data being read

*/

#include <p_getRdg.h>

byte *p_getRdg(FILE *in, rtype *ret)
{
    rtype ridge = READBYTE(in);
    natural chkn = ridge + P_DCORR;
    fletcher checksum;
    byte *buffer = calloc(P_RMAXSZ, sizeof(byte));

    P_FTADD(FUNCNAME);

    P_FINITF(checksum, in);

    if(!buffer || ferror(in))
    {
        perror(MSG_PERROR);
        *ret = errno;
        P_FREEALL();
        return NULL;
    }

    *ret = ridge - P_RTYPECORR;

    if(ridge <= P_DATA)
    {
        if(fread(buffer, sizeof(byte), ridge + P_DCORR, in) != ridge + P_DCORR)
        {
            p_print(MSG_BADRIDGE1);
            *ret = err_badRidge1;
            P_FREEALL();
            return NULL;
        }

        while(chkn--)
        {
            P_FDEC(buffer[chkn], checksum);
        }
    }

    P_FDEC(ridge, checksum);

    if(!P_FVALID(checksum))
    {
        p_print(MSG_BADFLETCHER);
        *ret = err_badFletcher;
        P_FREEALL();
        return NULL;
    }

    P_FTREM(FUNCNAME);

    return buffer;
}
