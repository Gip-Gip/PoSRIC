/* p_getRdg - gets the ridge from the specified file

ARGUMENTS:

FILE *in - the file being read
rType *ret - the ridge value

VARIABLES:

rType ridge - the ridge being read
natural chkn - the index that helps go through the data and subtract it from the
               checksum
fletcher checksum - the ridge checksum
byte *buffer - the buffer of data being read

*/

#include <p_getRdg.h>

dirTree p_getRdgDT;

byte *p_getRdg(FILE *in, rType *ret)
{
    rType ridge = READBYTE(in);
    natural chkn = ridge + P_DCORR, buffSz;
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

    switch(ridge)
    {
        case rType_dname:
            free(buffer);

            if(!(buffer = p_read(in, (retVal *)ret, &buffSz)) ||
                !(buffer = (byte *)p_dToS(buffer, buffSz, true, (retVal *)ret)) ||
                !P_DTADD(p_getRdgDT, (string)buffer) || !P_DTCURR(p_getRdgDT))
            {
                P_FREEALL();
                return NULL;
            }

            free(buffer);
            break;
        case rType_dend:
            if(!P_DTREM(p_getRdgDT) || !P_DTCURR(p_getRdgDT))
            {
                P_FREEALL();
                return NULL;
            }
            break;
        default:
            break;
    }

    P_FTREM(FUNCNAME);

    return buffer;
}
