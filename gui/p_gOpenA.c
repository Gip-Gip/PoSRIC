/* p_gOpenA - creates a files selection dialog and stores the file chosen into
              the global archive name

ARGUMENTS:

VARIABLES:

*/

#ifdef IUPGUI

#include <p_gOpenA.h>

gCallback p_gOpenA()
{
    Ihandle *fileDialog = IupFileDlg();

    IupSetAttribute(fileDialog, "DIALOGTYPE", "OPEN");

    IupPopup(fileDialog, IUP_CENTER, IUP_CENTER);

    if(IupGetInt(fileDialog, "STATUS") == IUP_NORMFILE)
        archiveName = IupGetAttribute(fileDialog, "VALUE");

    IupDestroy(fileDialog);

    IupSetAttribute(statusBar, "TITLE", archiveName);

    return IUP_CONTINUE;
}

#endif
