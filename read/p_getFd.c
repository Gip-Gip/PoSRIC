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
retval ret - used to hold errors
rtype ridge - the ridge value

*/

#include <p_getFd.h>

retval p_getFd(string inName, string outName, string name, bool overwrite)
{
    FILE *in = fopen(inName, READMODE), *out = NULL;
    byte *buffer = NULL;
    retval ret;
    rtype ridge;

    P_FTADD(FUNCNAME);

    if(!overwrite && (out = fopen(outName, READMODE)))
    {
        p_print(MSG_FILEEXISTS(outName));
        P_FREEALL();
        return err_fileExists;
    }

    if(!in || !(out = fopen(outName, WRITEMODE)))
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    if((ret = p_sCaC(in, NULL)) ||
        (ret = p_skpDtF(in, name)) ||
        (ret = p_skpDUU(in, rtype_fdata, rtype_fname, false)))
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
            fwrite(buffer, sizeof(byte), (ridge += P_DCORR), out) == ridge)

        free(buffer);

    if(ferror(out))
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    if(!buffer) return ridge;

    P_FREEALL();

    return none;
}
