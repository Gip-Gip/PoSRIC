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
    retVal ret = none;
    ssln cTime = ssln_new();

    P_FTADD(FUNCNAME); P_GDTINIT(inName, false);

    if(!in)
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    if((ridge = p_sCaC(in, NULL))) return ridge;

    p_print("%s\n", inName);

    while(ridge != rType_end &&
          (buffer = p_getRdg(in, &ridge)) &&
          ridge != rType_end)
    {
        free(buffer);

        while((ridge + P_RTYPECORR) > P_DATA && buffer)
        {
            switch(ridge)
            {
                case(rType_ctime):
                    free(cTime.integer);
                    cTime.integer = p_read(in, &ret, &cTime.integerSize);
                    p_print(MSG_CTIME(cTime));
                    break;

                case(rType_dname):
                    p_print(MSG_FILEFOUND2);
                    p_print(MSG_FILEFOUND1);
                    p_getRdgDT.dirCount --;
                    p_print(MSG_FILEFOUND1);
                    p_getRdgDT.dirCount ++;
                    p_print("%s", P_DTCURR(p_getRdgDT));
                    break;

                case(rType_fname):
                    p_print(MSG_FILEFOUND2);
                    p_print(MSG_FILEFOUND1);
                    while((buffer = p_getRdg(in, &ridge)) &&
                        (ridge += P_RTYPECORR) <= P_DATA &&
                        (buffer = p_dToS(buffer, ridge + P_DCORR, true, &ret)))
                    {
                        p_print(buffer);
                        free(buffer);
                    }

                    if(ret)
                    {
                        P_FREEALL();
                        return ret;
                    }

                    if(buffer) free(buffer);
                    if(ridge == rType_end) buffer = NULL;
                    break;

                default:
                    break;
            }
            ridge -= P_RTYPECORR;
        }
    }

    p_print(MSG_FILEFOUND2);

    if(!buffer)
    {
        P_FREEALL();
        return ridge;
    }

    P_FREEALL();
    return none;
}
