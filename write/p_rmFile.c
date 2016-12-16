/* p_rmFile - removes the file from the given archive

ARGUMENTS:

VARIABLES:

*/

#include <p_rmFile.h>

retval p_rmFile(string inName, string tmpName, string name, bool overwrite)
{
    FILE *in = fopen(inName, READMODE), *tmp = NULL;
    retval ret, ret2;

    P_FTADD(FUNCNAME);

    if(!overwrite && (tmp = fopen(tmpName, READMODE)))
    {
        p_print(MSG_FILEEXISTS(tmpName));
        P_FREEALL();
        return err_fileExists;
    }

    if(!in || !(tmp = fopen(tmpName, WRITEMODE)))
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    if((ret = p_sCaC(in, tmp)) ||
        (ret = p_cpyExc(in, tmp, name, &ret2)) || ret2 != err_nameExists ||
        (ret = p_skpDtU(in, rtype_fname, true)) ||
        (ret = p_cpyExc(in, tmp, name, &ret2)) ||
        (ret = p_wrtRdg(tmp, rtype_end, NULL)))
    {
        if(!ret) p_print(MSG_NAMEDEXIST(name));

        P_FREEALL();

        return ret ? ret : err_nameDexist;
    }

    if(remove(inName) || rename(tmpName, inName))
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    P_FREEALL();

    return none;
}
