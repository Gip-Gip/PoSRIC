/* p_getFd - reads filedata from an archive and writes the data to the given
             file

ARGUMENTS:

string inName - the name of the archive to use
string outName - the name of the file to write to
string name - the name of the in-archive file
bool overwrite - if set p_getFd won't give up if a file exists

VARIABLES:

FILE *in - the file pointer to the archive
FILE *out - the file pointer to the file being written to
byte *buffer - the buffer that holds the data returned by p_getRdg
retVal ret - used to hold errors
rType ridge - the ridge value

*/

#include <p_getFd.h>

retVal p_getFd(string inName, string outName, string name, dirTree dt,
    bool overwrite)
{
    FILE *in = fopen(inName, READMODE), *out = NULL;
    byte *buffer = NULL;
    retVal ret;
    rType ridge;

    P_FTADD(FUNCNAME); P_GDTINIT(inName, false);

    if(!overwrite && (out = fopen(outName, READMODE)))
    {
        p_print(MSG_FILEEXISTS(outName));
        P_FREEALL();
        return err_fileExists;
    }

    if(!in || !(out = fopen(outName, WRITEMODE)))
    {
        p_print(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    if((ret = p_sCaC(in, NULL)) ||
        (ret = p_skpDtF(in, name, dt)) ||
        (ret = p_skpDUU(in, rType_fdata, rType_fname, false)))
    {
        if(ret == err_brkRidge)
        {
            p_print(MSG_EMPTYFILE(name));
            P_FREEALL();
            return err_emptyFile;
        }

        P_FREEALL();
        return ret;
    }

    while((buffer = p_getRdg(in, &ridge)) && (ridge += P_RTYPECORR) <= P_DATA &&
            fwrite(buffer, sizeof(byte), (ridge + P_DCORR), out) ==
                ridge + P_DCORR)

        free(buffer);

    if(ferror(out))
    {
        p_print(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    if(!buffer) return ridge;

    P_FREEALL();

    return none;
}
