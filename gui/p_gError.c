/* p_gError - makes a dialog with the given error code

ARGUMENTS:

retVal error - the error to print

VARIABLES:

*/

#ifdef IUPGUI

#include <p_gError.h>

void p_gError(retVal error)
{
    IupMessage(
        GUI_MSG_ERROR,
        error < err_errno ? p_guiErrors[error] : strerror(errno));
}

#endif
