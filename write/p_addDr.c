/* p_addDr - adds a directory to the archive in use

ARGUMENTS:

string inName - the name of the archive to use
string tmpName - the name of the temporary file to use
string name - the filename to add to the archive
bool overwrite - if set p_addFn won't give up if a file exists

VARIABLES:

FILE *in - the file pointer to the archive being read
FILE *tmp - the file pointer to the temporary file
retVal ret - used to store errors
retVal cmpret - used to check if the file already exists

*/

#include <p_addDr.h>

retVal p_addDr(string inName, string tmpName, string name, bool overwrite,
    dirTree dt)
{
    FILE *in = fopen(inName, READMODE), *tmp = NULL;
    retVal ret, cmpret;
    time_t currTime;
    struct tm unixTime, currGMT;
    ssln currUtime;

    time(&currTime);
    currGMT = *gmtime(&currTime);
    P_INITUNIXT(unixTime);
    currUtime = ssln_i2n(difftime(mktime(&currGMT), mktime(&unixTime)));

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
        (ret = p_cpyExc(in, tmp, name, rType_dname, &cmpret, dt)) ||
        cmpret == err_nameExists || !P_DTCMP(dt, p_getRdgDT) ||
        (ret = p_wrtRdg(tmp, rType_dname, NULL)) ||
        (ret = p_write((byte *)name, strlen(name), tmp)) ||
        (ret = p_wrtRdg(tmp, rType_ctime, NULL)) ||
        (ret = p_write((byte *)currUtime.integer, currUtime.integerSize, tmp))||
        (ret = p_wrtRdg(tmp, rType_dend, NULL)) ||
        (cmpret == err_inDir ? (ret = p_copy(in, tmp)) : none) ||
        (ret = p_wrtRdg(tmp, rType_end, NULL)))
    {
        if(cmpret == err_nameExists) p_print(MSG_DIREXISTS(name));
        else if(!P_DTCMP(dt, p_getRdgDT)) p_print(MSG_DIRDEXIST(dt));

        P_FREEALL();

        return ret ? ret : cmpret;
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
