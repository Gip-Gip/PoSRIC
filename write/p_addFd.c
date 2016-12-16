/* p_addFd - adds file data to the given filename

ARGUMENTS:

string inName - the name of the archive being used
string tmpName - the name of the temporary file being used
string name - the name of the file being written to
natural buffSz - the size of the buffer divided by 128

VARIABLES:

*/

#include <p_addFd.h>

retval p_addFd(string inName, string tmpName, string name, string fName,
               bool overwrite, natural buffSz)
{
    FILE *in = fopen(inName, READMODE), *dataFile = fopen(name, READMODE),
    *tmp = NULL;
    byte *buffer = calloc(buffSz *= P_RMAXSZ, sizeof(byte));
    retval ret, ret2;
    natural cmpret;

    P_FTADD(FUNCNAME);

    if(!overwrite && (tmp = fopen(tmpName, READMODE)))
    {
        p_print(MSG_FILEEXISTS(tmpName));
        P_FREEALL();
        return err_fileExists;
    }

    if(!in || !dataFile || !(tmp = fopen(tmpName, WRITEMODE)))
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    if((ret = p_sCaC(in, tmp)) ||
        (ret = p_cpyExc(in, tmp, fName, &ret2)) || ret2 != err_nameExists ||
        (ret = p_skpDta(in, true)) ||
        (ret = p_wrtRdg(tmp, rtype_fname, NULL)) ||
        (ret = p_write((byte *)fName, strlen(fName), tmp)) ||
        (ret = p_wrtRdg(tmp, rtype_fdata, NULL)))
    {
        P_FREEALL();

        if(!ret) ((ret = p_addFn(inName, tmpName, fName, overwrite)) ||
                (ret = p_addFd( inName, tmpName, name, fName, overwrite,
                    buffSz / P_RMAXSZ)));

        return ret;
    }

    while((cmpret = fread(buffer, sizeof(byte), buffSz, dataFile)) == buffSz)
        p_write(buffer, buffSz, tmp);

    if(!ferror(dataFile))
    {
        if(cmpret) p_write(buffer, cmpret, tmp);
    }

    else
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    if((ret = p_cpyExc(in, tmp, name, &ret2)) || ret2 == err_nameExists ||
       (ret = p_wrtRdg(tmp, rtype_end, NULL)))
    {
        if(!ret) p_print(MSG_NAMEDUPED(name));

        P_FREEALL();

        return ret ? ret : err_nameDuped;
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
