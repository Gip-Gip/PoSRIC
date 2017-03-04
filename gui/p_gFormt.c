/* p_gFormt - formats the archive in use

ARGUMENTS:

VARIABLES:

*/

#ifdef IUPGUI
#include <p_gFormt.h>

gCallback p_gFormt()
{
    retVal ret;
    bool overwrite = false;

    if(!archiveName)
    {
        p_gError(err_archiveNset);
        return IUP_CONTINUE;
    }

    if(p_flExst(archiveName) && !(overwrite = p_gOvrWd()))
        return IUP_CONTINUE;

    if((ret = p_format(archiveName, overwrite)) != none)
    {
        p_gError(ret);
        return IUP_CONTINUE;
    }

    return IUP_CONTINUE;
}

#endif
