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
    dirTree workingDt;

    if(!currDir)
    {
        p_print(MSG_PERROR);
        return errno;
    }

    P_DTCOPY(workingDt, dt);

    while(entry = p_oGetDf(currDir))
    {
        currName = p_strapp(name, entry, false, false);

        p_addFd
        (
            inName,
            tmpName,
            currName,
            entry,
            overwrite,
            buffSz,
            workingDt
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

        p_addDr(inName, tmpName, entry, overwrite, dt);
        P_DTADD(workingDt, entry, true);
        p_oRecD(inName, tmpName, currName, overwrite, buffSz, workingDt);
        P_DTREM(workingDt, errno);
        free(currName);
    }

    P_DTDINIT(workingDt);

    closedir(currDir);

    return none;
}

