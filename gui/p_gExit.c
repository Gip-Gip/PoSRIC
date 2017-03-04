/* p_gExit - sends the exit signal to IUP

ARGUMENTS:

VARIABLES:

*/

#ifdef IUPGUI

#include <p_gExit.h>

gCallback p_gExit()
{
    return IUP_CLOSE;
}

#endif
