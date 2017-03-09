/* p_oGetDf - gets a filename from a directory entry

ARGUMENTS:

VARIABLES:

*/

#include <p_oCommn.h>

string p_oGetDf(DIR *directory)
{
    struct dirent *currDirEnt;
    string ret = calloc(STRALLOC, sizeof(char));

    while((currDirEnt = readdir(directory)))
        if(currDirEnt->d_type != DT_DIR && currDirEnt->d_name[0] != '.')

        return p_strapp(ret, currDirEnt->d_name, true, false);

    return NULL;
}
