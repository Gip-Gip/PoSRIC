/* p_stat - prints the properties of a single file or directory in an archive

ARGUMENTS:

string inName - the name of the archive being read
string name - the name of the file or directory being stat'd

VARIABLES:

FILE *in - the archive file pointer
rType ridge - stores the ridge in use

*/

#include <p_stat.h>

retVal p_stat(string inName, string name, dirTree dt)
{
    FILE *in = fopen(inName, READMODE);
    byte *buffer = NULL;
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

    if
    (
        (ret = p_sCaC(in, NULL)) ||
        (ret = p_skpDtF(in, name, dt))
    )
    {
        P_FREEALL();
        return ret;
    }

    p_print("\n%s\n", name);

    while
    (
        (buffer = p_getRdg(in, &ridge)) &&
        (ridge + P_RTYPECORR > P_DATA ? p_msCrAa(ridge, p_fileRdgs) : true)
    )
    {
        free(buffer);

        switch(ridge)
        {
            case(rType_addtime):
                free(cTime.integer);
                cTime.integer = p_read(in, &ret, &cTime.integerSize);
                ssln_set(&cTime, p_ut2lt(cTime));
                p_print(MSG_ADDTIME(cTime));
                p_print(MSG_ATTEND);
                break;

            case(rType_atime):
                free(cTime.integer);
                cTime.integer = p_read(in, &ret, &cTime.integerSize);
                ssln_set(&cTime, p_ut2lt(cTime));
                p_print(MSG_ATIME(cTime));
                p_print(MSG_ATTEND);
                break;

            case(rType_mtime):
                free(cTime.integer);
                cTime.integer = p_read(in, &ret, &cTime.integerSize);
                ssln_set(&cTime, p_ut2lt(cTime));
                p_print(MSG_MTIME(cTime));
                p_print(MSG_ATTEND);
                break;

            case(rType_ctime):
                free(cTime.integer);
                cTime.integer = p_read(in, &ret, &cTime.integerSize);
                ssln_set(&cTime, p_ut2lt(cTime));
                p_print(MSG_CTIME(cTime));
                p_print(MSG_ATTEND);
                break;

            default:
                break;
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
