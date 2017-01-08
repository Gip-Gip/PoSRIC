/* p_list - prints found files in the archive

ARGUMENTS:

string inName - the name of the archive being read

VARIABLES:

FILE *in - the archive file pointer
byte *buffer - the raw ridge buffer
string buffer2 - the buffer printed to the screen
rType ridge - stores the ridge in use

*/

#include <p_list.h>

retVal p_list(string inName)
{
    FILE *in = fopen(inName, READMODE);
    byte *buffer = NULL;
    string buffer2 = NULL;
    rType ridge;

    P_FTADD(FUNCNAME);

    if(!in)
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    if((ridge = p_sCaC(in, NULL))) return ridge;

    while(ridge != rType_end && (buffer = p_getRdg(in, &ridge)) && ridge != rType_end)
    {
        free(buffer);

        while(ridge == rType_fname && buffer)
        {
            p_print(MSG_FILEFOUND1);

            while((buffer = p_getRdg(in, &ridge)) &&
                (ridge += P_RTYPECORR) <= P_DATA)
            {
                if(!(buffer2 = calloc(
                        (ridge += P_DCORR) + STRALLOC, sizeof(string)))
                    || !memcpy(buffer2, buffer, ridge))
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
        return ridge;
    }

    P_FREEALL();
    return none;
}
