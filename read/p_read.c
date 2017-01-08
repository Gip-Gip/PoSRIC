/* p_read - reads an entire collection of data ridges to a buffer

ARGUMENTS:

FILE *in - the archive being read
retval *ret - the pointer to return the error to, if there is one

VARIABLES:

byte *preBuff - the pre-buffer buffer
byte *buffer - the buffer being returned
natural size - the size of the buffer

*/

#include <p_read.h>

byte *p_read(FILE *in, retVal *ret, natural *size)
{
    byte *preBuff, *buffer = calloc(STRALLOC, sizeof(char));
    rType rSize;

    *size = ZERO;

    P_FTADD(FUNCNAME);

    while((preBuff = p_getRdg(in, &rSize)) && (rSize += P_RTYPECORR) <= P_DATA)
    {
        if(!(buffer = realloc(buffer, *size += (rSize += P_DCORR))) ||
            memcpy(buffer + (*size - rSize), preBuff, rSize))
        {
            perror(MSG_PERROR);
            P_FREEALL();
            *ret = errno;
            return NULL;
        }

        free(preBuff);
    }

    return buffer;
}
