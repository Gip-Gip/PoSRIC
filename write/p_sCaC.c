/* p_sCaC - signature check and copy

ARGUMENTS:

VARIABLES:

*/

#include <p_sCaC.h>

retval p_sCaC(FILE *in, FILE *out)
{
    byte sigtest[P_SIGSZ];

    P_FTADD(FUNCNAME);

    if(fread(sigtest, sizeof(byte), P_SIGSZ, in) != P_SIGSZ)
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    if(memcmp(p_sig, sigtest, P_SIGSZ))
    {
        p_print(MSG_BADSIG);
        P_FREEALL();
        return err_badSig;
    }

    if(out && fwrite(p_sig, sizeof(byte), P_SIGSZ, out) != P_SIGSZ)
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    P_FREEALL();

    return none;
}
