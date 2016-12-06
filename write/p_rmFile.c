/* p_rmFile - removes the file from the given archive

ARGUMENTS:

VARIABLES:

*/

#include <p_rmFile.h>

retval p_rmFile(string inName, string tmpName, string name, bool overwrite)
{
    FILE *in = fopen(inName, READMODE), *tmp;
    retval ret, ret2;

    if(!overwrite && (tmp = fopen(tmpName, READMODE)))
    {
        p_print(MSG_FILEEXISTS(tmpName));
        fclose(tmp);
        if(in) free(in);
        return err_fileExists;
    }

    if(!in || !(tmp = fopen(tmpName, WRITEMODE)))
    {
        perror(MSG_PERROR);
        if(in) free(in);
        return errno;
    }

    if((ret = p_sCaC(in, tmp)) ||
        (ret = p_cpyExc(in, tmp, name, &ret2)) || ret2 != err_nameExists ||
        (ret = p_skpDtU(in, rtype_fname)) ||
        (ret = p_cpyExc(in, tmp, name, &ret2)) ||
        (ret = p_wrtRdg(tmp, rtype_end, NULL)))
    {
        fclose(in);
        fclose(tmp);

        if(!ret) p_print(MSG_NAMEDEXIST(name));

        return ret ? ret : err_nameDexist;
    }

    fclose(in);
    fclose(tmp);

    if(remove(inName) || rename(tmpName, inName))
    {
        perror(MSG_PERROR);
        return errno;
    }

    return none;
}
