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

struct status {
    bool readingDir;
} p_getRdgStatus;

bool p_dontRecDir = false;

byte *p_getRdg(FILE *in, rType *ret)
{
    rType ridge = READBYTE(in);
    natural chkn = ridge + P_DCORR, buffSz;
    fletcher checksum;
    byte *buffer = calloc(P_RMAXSZ, sizeof(byte));
    string dirBuffer;

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

    if(!p_dontRecDir) switch(ridge - P_RTYPECORR)
    {
        case rType_dname:
            p_getRdgStatus.readingDir = true;
            if(!(dirBuffer = (string)p_read(in, (retVal *)ret, &buffSz)) ||
                !(dirBuffer = p_dToS(
                    (byte *)dirBuffer, buffSz, true, (retVal *)ret)))
            {
                P_FREEALL();
                return NULL;
            }
            P_DTADD(p_getRdgDT, dirBuffer, true);
            break;

        case rType_dend:
            *ret = err_rootParent;
            P_DTREM(p_getRdgDT, NULL);
            *ret = rType_dend;
            break;

        default:
            break;
    }

    P_FTREM(FUNCNAME);

    *ret = ridge - P_RTYPECORR;

    return buffer;
}
