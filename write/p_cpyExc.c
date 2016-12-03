/* p_cpyExc - copies an archive, excluding the given file

ARGUMENTS:

FILE *in - a file pointer to the file being read
FILE *out - a file pointer to the file being written to

VARIABLES:

*/

#include <p_cpyExc.h>

retval p_cpyExc(FILE *in, FILE *out, string name)
{
    rtype ridge;
    retval ret;
    bool cmpret;
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

    for(buffer = p_getRdg(in, &ridge);
        !feof(in) && buffer && ridge != rtype_end;
        buffer = p_getRdg(in, &ridge))
    {
        if(ridge + P_RTYPECORR <= P_DATA)
            p_wrtRdg(out, ridge + P_RTYPECORR + P_DCORR, buffer);

        else if(ridge == rtype_fname)
        {
            if((cmpret = p_cmpDta((byte *)name, strlen(name), in)) == true &&
                (ret = p_skpDta(in)))
            {
                free(buffer);
                return ret;
            }

            else if(cmpret == neither)
            {
                perror(MSG_PERROR);
                return errno;
            }

            else if(cmpret == false) p_wrtRdg(out, ridge, NULL);
        }

        else if(ridge == rtype_null && (ret = p_skpDta(in))) return ret;

        else p_wrtRdg(out, ridge, NULL);

        free(buffer);
    }

    if(!buffer || errno)
    {
        if(buffer) free(buffer);
        perror(MSG_PERROR);
        return ridge;
    }

    free(buffer);

    return none;
}
