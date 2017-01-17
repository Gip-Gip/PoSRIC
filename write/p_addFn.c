/* p_addFn - adds a filename to the archive in use

ARGUMENTS:

string inName - the name of the archive to use
string tmpName - the name of the temporary file to use
string name - the filename to add to the archive
bool overwrite - if set p_addFn won't give up if a file exists
dirTree dt - the current directory tree in use

VARIABLES:

FILE *in - the file pointer to the archive being read
FILE *tmp - the file pointer to the temporary file
retVal ret - used to store errors
retVal ret2 - used to check if the file already exists

*/

#include <p_addFn.h>

retVal p_addFn(string inName, string tmpName, string name, bool overwrite,
    dirTree dt)
{
    FILE *in = fopen(inName, READMODE), *tmp = NULL;
    retVal ret, ret2;

    P_FTADD(FUNCNAME); P_GDTINIT(inName, false);

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
        (ret = p_cpyExc(in, tmp, name, rType_fname, &ret2, dt)) ||
        ret2 == err_nameExists ||
        (ret = p_wrtRdg(tmp, rType_fname, NULL)) ||
        (ret = p_write((byte *)name, strlen(name), tmp)) ||
        (ret2 == err_inDir ? (ret = p_copy(in, tmp)) : none) ||
        (ret = p_wrtRdg(tmp, rType_end, NULL)))
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
