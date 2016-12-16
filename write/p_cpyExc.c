/* p_cpyExc - copies an archive, excluding the given file

ARGUMENTS:

FILE *in - a file pointer to the file being read
FILE *out - a file pointer to the file being written to

VARIABLES:

*/

#include <p_cpyExc.h>

retval p_cpyExc(FILE *in, FILE *out, string name, retval *retptr)
{
    rtype ridge;
    retval ret;
    bool cmpret;
    byte *buffer;

    *retptr = none;

    P_FTADD(FUNCNAME);

    for(buffer = p_getRdg(in, &ridge);
        !feof(in) && buffer && ridge != rtype_end;
        buffer = p_getRdg(in, &ridge))
    {
        if(ridge + P_RTYPECORR <= P_DATA)
            p_wrtRdg(out, ridge + P_RTYPECORR + P_DCORR, buffer);

        else if(ridge == rtype_fname)
        {
            if((cmpret = p_cmpDta((byte *)name, strlen(name), in)) == true)
            {
                *retptr = err_nameExists;
                P_FREEALL();
                return none;
            }

            else if(cmpret == neither)
            {
                P_FREEALL();
                return err_unknown;
            }

            else if(cmpret == false) p_wrtRdg(out, ridge, NULL);
        }

        else if(ridge == rtype_null && (ret = p_skpDta(in, true)))
        {
            P_FREEALL();
            return ret;
        }

        else p_wrtRdg(out, ridge, NULL);

        free(buffer);
    }

    if(!buffer)
    {
        P_FREEALL();
        return ridge;
    }

    P_FREEALL();

    return none;
}
