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
    bool cmpret = false, inDir = false;
    byte *buffer;
    natural depthCount = dt.dirCount;

    *retptr = none;

    P_FTADD(FUNCNAME);

    for(buffer = p_getRdg(in, &ridge);
        !feof(in) && buffer && ridge != rType_end;
        buffer = p_getRdg(in, &ridge))
    {
        if(P_DTCMP(dt, p_getRdgDT) && !inDir) inDir = true;

        else if(!P_DTCMP(dt, p_getRdgDT) && inDir)
        {
            /* We could've changed into the directory we're looking for... */
            if(cmpRdg == rType_dname && !strcmp(P_DTCURR(p_getRdgDT), name))
            {
                *retptr = err_nameExists;
                P_FREEALL();
                return none;
            }

            /* We also shouldn't give up if we enter a subdirectory. Just set
               inDir to false */
            if(depthCount <= p_getRdgDT.dirCount && cmpRdg == rType_dname)
                inDir = false;

            else
            {
                fseek(in, -P_RMINRD, SEEK_CUR);
                P_DTDINIT(p_getRdgDT);
                P_DTCOPY(p_getRdgDT, dt);
                *retptr = err_inDir;
                P_FREEALL();
                return none;
            }
        }

        if(ridge + P_RTYPECORR <= P_DATA)
            p_wrtRdg(out, ridge + P_RTYPECORR + P_DCORR, buffer);

        else if(ridge == cmpRdg)
        {
            if(inDir)
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

                else p_wrtRdg(out, ridge, NULL);
            }

            else p_wrtRdg(out, ridge, NULL);
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
