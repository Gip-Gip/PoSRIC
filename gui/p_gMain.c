/* p_gMain - if the GUI is enabled will initialize the graphics and call all
             the functions

ARGUMENTS:

VARIABLES:

*/

#ifndef IUPGUI

#include <p_messag.h>

retVal p_gMain()
{
    p_print(MSG_NOGUI);
    return err_noGui;
}

#else

#include <p_gMain.h>

Ihandle *statusBar;

retVal p_gMain()
{
    retVal ret;
    Ihandle *window, *veiwport, *menu, *posricMenu, *fileMenu,
        *exitHandle, *openHandle, *formatHandle;

    if((ret = IupOpen(NULL, NULL)) != IUP_NOERROR)
    {
        P_FREEALL();
        return ret;
    }

    /* PoSRIC MENU */

    IupSetCallback(
        exitHandle = IupItem("Exit", NULL),
        "ACTION",
        (Icallback)p_gExit);

    posricMenu = IupSubmenu(GUI_PROGNAME, IupMenu(exitHandle, NULL));

    /* FILE MENU */

    IupSetCallback(
        openHandle = IupItem("Open Archive", NULL),
        "ACTION",
        (Icallback)p_gOpenA);

    IupSetCallback(
        formatHandle = IupItem("Format Archive", NULL),
        "ACTION",
        (Icallback)p_gFormt);

    fileMenu = IupSubmenu("File", IupMenu(openHandle, formatHandle, NULL));

    /* GENERAL LAYOUT */

    menu = IupMenu(posricMenu, fileMenu, NULL);
    statusBar = IupLabel(GUI_TITLE);
    veiwport = IupHbox(statusBar, NULL);
    window = IupDialog(veiwport);
    IupSetAttributeHandle(window, "MENU", menu);
    IupSetAttribute(window, "SIZE", "HALFxHALF");
    IupSetAttribute(window, "TITLE", GUI_TITLE);

    IupShow(window);

    IupMainLoop();

    P_FREEALL();
    return none;
}

#endif
