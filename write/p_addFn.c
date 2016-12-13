/* posric_addFilename - adds a filename to the archive in use

ARGUMENTS:

string inName - the filename of the archive in use

VARIABLES:

*/

#include <p_addFn.h>

retval p_addFn(string inName, string tmpName, string name, bool overwrite)
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
        (ret = p_cpyExc(in, tmp, name, &ret2)) || ret2 ||
        (ret = p_wrtRdg(tmp, rtype_fname, NULL)) ||
        (ret = p_write((byte *)name, strlen(name), tmp)) ||
        (ret = p_wrtRdg(tmp, rtype_end, NULL)))
    {
        if(ret2 == err_nameExists) p_print(MSG_NAMEEXISTS(name));

        P_FREEALL();

        return ret ? ret : ret2;
    }

    fclose(in); in = NULL;
    fclose(tmp); tmp = NULL;

    if(remove(inName) || rename(tmpName, inName))
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    P_FREEALL();
    return none;
}
