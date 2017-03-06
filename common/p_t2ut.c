/* p_t2ut - converts the system's time_t type into the project-wide UNIX-Time
            SSLN format

ARGUMENTS:

time_t srcTime - the time to convert

VARIABLES:

struct tm unixTime - used to convert to UNIX time

*/

#include <p_t2ut.h>

ssln p_t2ut(time_t srcTime)
{
    struct tm unixTime, srcGMT;

    if(srcTime < 0) return ssln_eEr(err_unknown);

    srcGMT = *gmtime(&srcTime);
    P_INITUNIXT(unixTime);

    return ssln_i2n(difftime(mktime(&srcGMT), mktime(&unixTime)));
}
