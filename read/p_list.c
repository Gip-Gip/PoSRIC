/* p_list - prints found files in the archive

ARGUMENTS:

string inName - the name of the archive being read

VARIABLES:

FILE *in - the archive file

*/

#include <p_list.h>

retval p_list(string inName)
{
    FILE *in = fopen(inName, READMODE);
    byte *buffer = NULL;
    string buffer2 = NULL;
    rtype ret;

    P_FTADD(FUNCNAME);

    if(!in)
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    if((ret = p_sCaC(in, NULL))) return ret;

    while((buffer = p_getRdg(in, &ret)) && ret != rtype_end)
    {
        free(buffer);

        while(ret == rtype_fname && buffer)
        {
            p_print(MSG_FILEFOUND1);

            while((buffer = p_getRdg(in, &ret)) &&
                (ret += P_RTYPECORR) <= P_DATA)
            {
                if(!(buffer2 = calloc(
                        (ret += P_DCORR) + STRALLOC, sizeof(string)))
                    || !memcpy(buffer2, buffer, ret))
                {
                    perror(MSG_PERROR);
                    P_FREEALL();
                    return errno;
                }

                p_print(buffer2);
                free(buffer);
                free(buffer2); buffer2 = NULL;
            }

            p_print(MSG_FILEFOUND2);

            if(buffer) free(buffer);
        }
    }

    if(!buffer)
    {
        P_FREEALL();
        return ret;
    }

    P_FREEALL();
    return none;
}
