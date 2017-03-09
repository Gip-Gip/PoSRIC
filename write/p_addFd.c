/* p_addFd - adds file data to the given filename

ARGUMENTS:

string inName - the srcName of the archive being used
string tmpName - the srcName of the temporary file being used
string srcName - the srcName of the file being written to
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

retVal p_addFd
(
    string inName,
    string tmpName,
    string srcName,
    string name,
    bool overwrite,
    natural buffSz,
    dirTree dt
)
{
    FILE *in = fopen(inName, READMODE), *dataFile = fopen(srcName, READMODE),
    *tmp = NULL;
    byte *buffer = calloc(buffSz *= P_RMAXSZ, sizeof(byte));
    retVal ret, cmpret;
    natural readSize;
    ssln creTime = ssln_new(), modTime = ssln_new(), accTime = ssln_new();
    ssln currTime;

    currTime = p_t2ut(time(NULL));

    P_FTADD(FUNCNAME); P_GDTINIT(inName, false);

    if(!overwrite && (tmp = fopen(tmpName, READMODE)))
    {
        p_print(MSG_FILEEXISTS(tmpName));
        P_FREEALL();
        return err_fileExists;
    }

    if(!in || !dataFile || !(tmp = fopen(tmpName, WRITEMODE)))
    {
        p_print(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    p_oGetTs(srcName, &creTime, &modTime, &accTime);

    /* Since all these can throw errors, why not just clump them into one giant
       if statement? */
    if
    (
        (ret = p_sCaC(in, tmp)) ||
        (ret = p_cpyExc(in, tmp, name, rType_fname, &cmpret, dt)) ||
        cmpret != err_nameExists ||
        /* To prevent weird append-like results, just re-write the file */
        (ret = overwrite ? none : err_fileExists) ||
        (ret = p_skpFil(in, true)) ||
        (ret = p_wrtRdg(tmp, rType_fname, NULL)) ||
        (ret = p_write((byte *)name, strlen(name), tmp)) ||
        /* All these calls re-write timestamps. Ugly! */
        (ret = p_wrtRdg(tmp, rType_addtime, NULL)) ||
        (ret = p_write((byte *)currTime.integer, currTime.integerSize, tmp)) ||
        (ret = p_wrtRdg(tmp, rType_ctime, NULL)) ||
        (ret = p_write((byte *)creTime.integer, creTime.integerSize, tmp)) ||
        (ret = p_wrtRdg(tmp, rType_mtime, NULL)) ||
        (ret = p_write((byte *)modTime.integer, modTime.integerSize, tmp)) ||
        (ret = p_wrtRdg(tmp, rType_atime, NULL)) ||
        (ret = p_write((byte *)accTime.integer, accTime.integerSize, tmp)) ||
        (ret = p_wrtRdg(tmp, rType_fdata, NULL))
    )
    {
        /* No error means no existance! */
        if(!ret && P_DTCMP(dt, p_getRdgDT))
        {
            P_FREEALL();
            P_FTADD(FUNCNAME);
            in = NULL, tmp = NULL;
            ret = p_addFn(inName, tmpName, name, overwrite, dt);

            if(!ret)
            {
                ret = p_addFd
                (
                    inName,
                    tmpName,
                    srcName,
                    name,
                    overwrite,
                    buffSz / P_RMAXSZ,
                    dt
                );
            }

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
        p_print(MSG_PERROR);
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
        p_print(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    P_FREEALL();

    return none;
}
