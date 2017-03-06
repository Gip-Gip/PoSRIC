/* p_addFd - adds file data to the given filename

ARGUMENTS:

string inName - the name of the archive being used
string tmpName - the name of the temporary file being used
string name - the name of the file being written to
natural buffSz - the size of the buffer divided by 128

VARIABLES:

FILE *in - the archive being read
FILE *dataFile - the file the data is read from
FILE *tmp - the file pointer to the temporary file
byte *buffer - the buffer used for temporarily storing file data
retVal ret - used for holding errors
retVal cmpret - used for checking for a file's existence
natural readSize - used to get the size of each fread

*/

#include <p_addFd.h>

retVal p_addFd(string inName, string tmpName, string name, string fName,
               bool overwrite, natural buffSz, dirTree dt)
{
    FILE *in = fopen(inName, READMODE), *dataFile = fopen(name, READMODE),
    *tmp = NULL;
    byte *buffer = calloc(buffSz *= P_RMAXSZ, sizeof(byte));
    retVal ret, cmpret;
    natural readSize;
    ssln creTime = ssln_new(), modTime = ssln_new(), accTime = ssln_new();

    p_oGetTs(name, &creTime, &modTime, &accTime);

    P_FTADD(FUNCNAME); P_GDTINIT(inName, false);

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
        (ret = p_cpyExc(in, tmp, fName, rType_fname, &cmpret, dt)) ||
        cmpret != err_nameExists ||
        (ret = p_skpDta(in, true)) ||
        (ret = p_wrtRdg(tmp, rType_fname, NULL)) ||
        (ret = p_write((byte *)fName, strlen(fName), tmp)) ||
        (ret = p_wrtRdg(tmp, rType_mtime, NULL)) ||
        (ret = p_write((byte *)modTime.integer, modTime.integerSize, tmp)) ||
        (ret = p_wrtRdg(tmp, rType_fdata, NULL)))
    {
        if(!ret && P_DTCMP(dt, p_getRdgDT))
        {
            P_FREEALL();
            P_FTADD(FUNCNAME);
            in = NULL, tmp = NULL;
            ret = p_addFn(inName, tmpName, fName, overwrite, dt);

            if(!ret)
                ret = p_addFd( inName, tmpName, name, fName, overwrite,
                    buffSz / P_RMAXSZ, dt);
            P_FTREM(FUNCNAME);
        }

        else if(!ret)
        {
            p_print(MSG_DIRDEXIST(dt));
            P_FREEALL();
            return err_dirDexist;
        }

        else P_FREEALL();

        return ret;
    }

    while((readSize = fread(buffer, sizeof(byte), buffSz, dataFile)) == buffSz)
        p_write(buffer, buffSz, tmp);

    if(!ferror(dataFile))
    {
        if(readSize) p_write(buffer, readSize, tmp);
    }

    else
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    if((ret = p_copy(in, tmp)) ||
       (ret = p_wrtRdg(tmp, rType_end, NULL)))
    {
        P_FREEALL();
        return ret;
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
