/* p_getFd - reads filedata and writes it to the given file

ARGUMENTS:

VARIABLES:

*/

#include <p_getFd.h>

retval p_getFd(string inName, string outName, string name, bool overwrite)
{
    FILE *in = fopen(inName, READMODE), *out = NULL;
    byte *buffer = NULL;
    retval ret;
    rtype ret2;

    P_FTADD(FUNCNAME);

    if(!overwrite && (out = fopen(outName, READMODE)))
    {
        p_print(MSG_FILEEXISTS(outName));
        P_FREEALL();
        return err_fileExists;
    }

    if(!in || !(out = fopen(outName, WRITEMODE)))
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    if((ret = p_sCaC(in, NULL)) ||
        (ret = p_skpDtF(in, name)) ||
        (ret = p_skpDUU(in, rtype_fdata, rtype_fname, false)))
    {
        if(ret == err_brkRidge)
        {
            p_print(MSG_EMPTYFILE(name));
            P_FREEALL();
            return err_emptyFile;
        }

        P_FREEALL();
        return ret;
    }

    while((buffer = p_getRdg(in, &ret2)) && (ret2 += P_RTYPECORR) <= P_DATA &&
            fwrite(buffer, sizeof(byte), (ret2 += P_DCORR), out) == ret2)

        free(buffer);

    if(ferror(out))
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    if(!buffer) return ret2;

    P_FREEALL();

    return none;
}
