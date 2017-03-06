/* p_ut2lt - converts UNIX-Time(GMT) to Local Time

ARGUMENTS:

ssln srcTime - the time to convert

VARIABLES:

*/

#include <p_ut2lt.h>

ssln p_ut2lt(ssln srcTime)
{
    struct tm GMTcurr, localCurr;
    time_t baseCurr;

    time(&baseCurr);

    localCurr = *localtime(&baseCurr);
    GMTcurr = *gmtime(&baseCurr);

    return ssln_sub
    (
        srcTime,
        ssln_i2n((natural)difftime(mktime(&GMTcurr), mktime(&localCurr)))
    );
}
