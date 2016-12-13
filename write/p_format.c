/* posric_format - formats the given file

ARGUMENTS:

string outName - the name of the file to format

VARIABLES:

*/

#include <p_format.h>

retval p_format(string outName, bool overwrite)
{
    FILE *outFile;

    P_FTADD(FUNCNAME);

    if(!overwrite && (outFile = fopen(outName, READMODE)))
    {
        p_print(MSG_FILEEXISTS(outName));
        P_FREEALL();
        return err_fileExists;
    }

    if(!(outFile = fopen(outName, WRITEMODE)))
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    if(fwrite(p_sig, sizeof(byte), P_SIGSZ, outFile) != P_SIGSZ ||
        p_wrtRdg(outFile, rtype_end, NULL))
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    P_FREEALL();

    return none;
}
