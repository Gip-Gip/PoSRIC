/* p_oGetTs - gets the timestamps of a file

ARGUMENTS:

string name - the name of the file to get the timestamp from

VARIABLES:

*/

#include <p_oGetTs.h>

void p_oGetTs(string name, ssln *creT, ssln *modT, ssln *accT)
{
    struct stat statvar;

    stat(name, &statvar);

    ssln_set(creT, p_t2ut(statvar.st_mtime));
    ssln_set(modT, p_t2ut(statvar.st_mtime));
    ssln_set(accT, p_t2ut(statvar.st_atime));
}
