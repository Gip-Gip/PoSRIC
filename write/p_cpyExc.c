/* p_cpyExc - copies an archive, excluding the given file

ARGUMENTS:

FILE *in - a file pointer to the file being read
FILE *out - a file pointer to the file being written to
string name - the name of the file to give up on
retVal *retptr - the pointer written to if the file is encountered

VARIABLES:

rType ridge - the ridge being compared to
retVal ret - used to store errors
bool cmpret - used to store values for boolean comparison
byte *buffer - the ridge buffer

*/

#include <p_cpyExc.h>

retVal p_cpyExc(FILE *in, FILE *out, string name, rType cmpRdg, retVal *retptr,
    dirTree dt)
{
    rType ridge;
    retVal ret;
    bool cmpret = false;
    byte *buffer;

    *retptr = none;

    P_FTADD(FUNCNAME);

    for(buffer = p_getRdg(in, &ridge);
        !feof(in) && buffer && ridge != rType_end;
        buffer = p_getRdg(in, &ridge))
    {
        if(ridge + P_RTYPECORR <= P_DATA)
            p_wrtRdg(out, ridge + P_RTYPECORR + P_DCORR, buffer);

        else if(ridge == cmpRdg)
        {
            if(P_DTCMP(dt, p_getRdgDT) &&
                (cmpret = p_cmpDta((byte *)name, strlen(name), in)) == true)
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

        else if(ridge == rType_null && (ret = p_skpDta(in, true)))
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
