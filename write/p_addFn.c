/* posric_addFilename - adds a filename to the archive in use

ARGUMENTS:

string inName - the filename of the archive in use

VARIABLES:

*/

#include <p_addFn.h>

retval p_addFn(string inName, string tmpName, string name, bool overwrite)
{
    FILE *in = fopen(inName, READMODE), *tmp;
    retval ret, ret2;

    if(!overwrite && (tmp = fopen(tmpName, READMODE)))
    {
        p_print(MSG_FILEEXISTS(tmpName));
        fclose(tmp);
        if(in) fclose(in);
        return err_fileExists;
    }

    if(!in || !(tmp = fopen(tmpName, WRITEMODE)))
    {
        perror(MSG_PERROR);
        if(in) fclose(in);
        return errno;
    }

    if((ret = p_sCaC(in, tmp)) ||
        (ret = p_cpyExc(in, tmp, name, &ret2)) || ret2 ||
        (ret = p_wrtRdg(tmp, rtype_fname, NULL)) ||
        (ret = p_write((byte *)name, strlen(name), tmp)) ||
        (ret = p_wrtRdg(tmp, rtype_end, NULL)))
    {
        fclose(in);
        fclose(tmp);

        if(ret2 == err_nameExists) p_print(MSG_NAMEEXISTS(name));

        return ret ? ret : ret2;
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
