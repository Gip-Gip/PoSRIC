/* p_rmDir - removes the directory from the given archive

ARGUMENTS:

string inName - the name of the source archive
string tmpName - the name of the temporary file
string name - the name of the directory to remove from the archive
bool overwrite - if set p_rmFile will not give up if the tmpFile exists

VARIABLES:

FILE *in - the source archive as a file pointer
FILE *tmp - the temporary file as a file pointer
retVal ret - the primarary return variable
retVal ret2 - the secondary return variable; used with cpyExc to tell if the
              file was found

*/

#include <p_rmDir.h>

retVal p_rmDir(string inName, string tmpName, string name, bool overwrite,
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
        p_print(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    if((ret = p_sCaC(in, tmp)) ||
        (ret = p_cpyExc(in, tmp, name, rType_dname, &ret2, dt)) ||
        ret2 != err_nameExists ||
        (ret = p_skpDir(in)) ||
        (ret = p_copy(in, tmp)) ||
        (ret = p_wrtRdg(tmp, rType_end, NULL)))
    {
        if(!ret) p_print(MSG_NAMEDEXIST(name));

        P_FREEALL();

        return ret ? ret : err_nameDexist;
    }

    if(remove(inName) || rename(tmpName, inName))
    {
        P_FREEALL();
        return errno;
    }

    P_FREEALL();

    return none;
}
