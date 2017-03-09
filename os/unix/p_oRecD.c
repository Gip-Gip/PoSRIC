/* p_recDir - recurses the given directory

ARGUMENTS:

directory dir - the directory to recurse

VARIABLES:

*/

#include <p_oCommn.h>

retVal p_oRecD
(
    string inName,
    string tmpName,
    string name,
    bool overwrite,
    natural buffSz,
    dirTree dt
)
{
    DIR *currDir = opendir(name);
    string entry;
    string currName;

    if(!currDir)
    {
        p_print(MSG_PERROR);
        return errno;
    }

    while(entry = p_oGetDf(currDir))
    {
        currName = p_strapp(name, entry, false, false);

        p_print("[%s]", currName);

        p_addFd
        (
            inName,
            tmpName,
            currName,
            entry,
            overwrite,
            buffSz,
            dt
        );

        free(currName);
        free(entry);
    }

    closedir(currDir);
    currDir = opendir(name);

    while(entry = p_oGetDd(currDir))
    {
        currName = p_strapp(name, entry, false, false);
        currName = p_strapp(currName, P_ODIRDELEM, true, false);
        p_print("(%s)", currName);

        p_addDr(inName, tmpName, entry, overwrite, dt);
        P_DTADD(dt, entry, true);
        p_oRecD(inName, tmpName, currName, overwrite, buffSz, dt);
        P_DTREM(dt, errno);
        free(currName);
    }

    closedir(currDir);

    return none;
}
