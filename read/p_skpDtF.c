/* p_skpDtF - skips data until a file is found

ARGUMENTS:

FILE *in - the file being skipped through
string name - the name of the file to skip to

VARIABLES:

retVal ret - used to store errors
bool ret2 - used to store the return value of cmpDta

*/

#include <p_skpDtF.h>

retVal p_skpDtF(FILE *in, string name)
{
    retVal ret;
    bool ret2;

    P_FTADD(FUNCNAME);

    while(!feof(in))
    {
        if((ret = p_skpDtU(in, rType_fname, false)) ||
            (ret2 = p_cmpDta((byte *)name, strlen(name), in)) == neither)
        {
            if(ret == err_rNotFound) p_print(MSG_NAMEDEXIST(name));

            P_FREEALL();

            return ret ? ret : err_unknown;
        }

        if(ret2 == true)
        {
            ret = p_skpDta(in, true);
            P_FREEALL();
            return ret ? ret : none;
        }
    }

    p_print(MSG_NAMEDEXIST(name));
    P_FREEALL();
    return err_notFound;
}
