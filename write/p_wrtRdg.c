/* p_wrtRdg - write a ridge to the given file

ARGUMENTS:

FILE *out - the file being written to
byte *data - the data the ridge contains
natural size - the size of the data being written

VARIABLES:

fletcher checksum - the checksum to write to the archive
natural chkn - the index that helps go through the data and add it to the
               checksum

*/

#include <p_wrtRdg.h>

retval p_wrtRdg(FILE *out, rtype ridge, byte *data)
{
    fletcher checksum;
    natural chkn = INDEXINIT;

    P_FINIT(checksum);

    P_FTADD(FUNCNAME);

    if(data == NULL)
    {
        ridge += P_RTYPECORR;
        P_FINC(ridge, checksum);

        WRITEBYTE(ridge, out);
        P_FWRT(checksum, out);

        if(ferror(out))
        {
            perror(MSG_PERROR);
            P_FREEALL();
            return errno;
        }

        P_FREEALL();

        return none;
    }

    P_FINC(ridge - P_DCORR, checksum);

    while(++chkn < ridge)
    {
        P_FINC(data[chkn], checksum);
    }

    WRITEBYTE(ridge - P_DCORR, out);
    P_FWRT(checksum, out);

    if(fwrite(data, sizeof(byte), ridge, out) != ridge)
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    P_FREEALL();

    return none;
}
