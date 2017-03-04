/* p_flExst - checks if a file already exists

ARGUMENTS:

string name - the name of the file to check

VARIABLES:

*/

#include <p_flExst.h>

bool p_flExst(string name)
{
    FILE *file = fopen(name, READMODE);

    if(file)
    {
        fclose(file);
        return true;
    }

    return false;
}
