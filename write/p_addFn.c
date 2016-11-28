/* posric_addFilename - adds a filename to the archive in use

ARGUMENTS:

string inName - the filename of the archive in use

VARIABLES:

*/

#include <p_addFn.h>

retval p_addFn(string inName, string tmpName, string name)
{
    FILE *in = fopen(inName, READMODE), *tmp;
    retval ret;

    if(!overwrite && (tmp = fopen(tmpName, READMODE)))
    {
        p_print(MSG_FILEEXISTS(tmpName));
        fclose(tmp);
        return err_fileExists;
    }

    if(!in || !(tmp = fopen(tmpName, WRITEMODE)))
    {
        perror(MSG_PERROR);
        return errno;
    }

    if((ret = p_cpyExc(in, tmp, name)) ||
        (ret = p_wrtRdg(tmp, rtype_fname, NULL)) ||
        (ret = p_write(name, strlen(name), tmp)) ||
        (ret = p_wrtRdg(tmp, rtype_end, NULL)))
    {
        fclose(in);
        fclose(tmp);
        return ret;
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
