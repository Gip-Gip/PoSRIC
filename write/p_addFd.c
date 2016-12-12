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
        (ret = p_skpDta(in)) ||
        (ret = p_wrtRdg(tmp, rtype_fname, NULL)) ||
        (ret = p_write((byte *)fName, strlen(fName), tmp)) ||
        (ret = p_wrtRdg(tmp, rtype_fdata, NULL)))
    {
        P_FREEALL();

        if(!ret) p_print(MSG_NAMEDEXIST(fName));

        return ret ? ret : err_nameDexist;
    }

    fseek(in, strlen(fName) + P_RMINRD, SEEK_CUR);

    for(cmpret = fread(buffer, sizeof(byte), buffSz, dataFile);
        cmpret == buffSz;
        cmpret = fread(buffer, sizeof(byte), buffSz, dataFile))

        p_write(buffer, buffSz, tmp);

    if(feof(dataFile))
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
        P_FREEALL();

        if(!ret) p_print(MSG_NAMEDUPED(name));

        return ret ? ret : err_nameDuped;
    }

    P_FREEALL();

    if(remove(inName) || rename(tmpName, inName))
    {
        perror(MSG_PERROR);
        return errno;
    }

    return none;
}
