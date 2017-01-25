/* p_msCrAa - compares a ridge to an array of ridges

ARGUMENTS:

rType ridge - the ridge being compared
rType *cmpArray - the array ridge is being compared against

VARIABLES:

natural rdgn - the index used to go through cmpArray

*/

#include <p_msCrAa.h>

natural p_msCrAa(rType ridge, rType *cmpArray)
{
    natural rdgn = INDEXINIT;

    while(ridge != cmpArray[++rdgn] && cmpArray[rdgn] != rType_foo);

    if(cmpArray[rdgn] == rType_foo) return false;

    return true;
}
