/* p_cpyExc - copies an archive, excluding the given file

ARGUMENTS:

FILE *in - a file pointer to the file being read
FILE *out - a file pointer to the file being written to

VARIABLES:

*/

#include <p_cpyExc.h>

retval p_cpyExc(FILE *in, FILE *out, string name)
{
    rtype ret;
    byte *buffer, sigtest[P_SIGSZ];

    if(fread(sigtest, sizeof(byte), P_SIGSZ, in) != P_SIGSZ)
    {
        perror(MSG_PERROR);
        return errno;
    }

    if(memcmp(p_sig, sigtest, P_SIGSZ))
    {
        p_print(MSG_BADSIG);
        return err_badSig;
    }

    if(fwrite(p_sig, sizeof(byte), P_SIGSZ, out) != P_SIGSZ)
    {
        perror(MSG_PERROR);
        return errno;
    }

    for(buffer = p_getRdg(in, &ret);
        !feof(in) && buffer && ret != rtype_end;
        buffer = p_getRdg(in, &ret))
    {
        if(ret + P_RTYPECORR <= P_DATA)
            p_wrtRdg(out, ret + P_RTYPECORR + P_DCORR, buffer);
        else p_wrtRdg(out, ret, NULL);
        free(buffer);
    }

    if(!buffer) return ret;

    return none;
}
