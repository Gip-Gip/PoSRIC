/* p_dToS - converts a block of data to a string

ARGUMENTS:

byte *data - the data to convert
natural size - the size of the data
bool freeData - if set, p_dToS will free the data pointer
retval *ret - the pointer to return errors to

VARIABLES:

string stringRet - the string being returned

*/

#include <p_dToS.h>

string p_dToS(byte *data, natural size, bool freeData, retVal *ret)
{
    string stringRet = calloc(size + STRALLOC, sizeof(character));

    if(!ret || memcpy(stringRet, data, size))
    {
        perror(MSG_PERROR);
        *ret = errno;
        return NULL;
    }

    if(freeData) free(data);

    return stringRet;
}
