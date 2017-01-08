/* p_msCmpS - compares two arrays of strings

ARGUMENTS:

VARIABLES:

*/

#include <p_msCmpS.h>

bool p_msCmpS(string *arr1, string *arr2, natural size)
{
    while(size --) if(strcmp(arr1[size], arr2[size])) return false;

    return true;
}
