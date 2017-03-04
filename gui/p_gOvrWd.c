

#ifdef IUPGUI

#include <p_gOvrWd.h>

gCallback p_gStFlg(bool *flag, bool state, natural ret)
{
    *flag = state;
    return ret;
}

bool p_gOvrWd()
{
    Ihandle *dialog, *message, *yesHandle, *noHandle;
    bool overwrite = false;

    message = IupLabel(GUI_MSG_OVRWRT);

    yesHandle = IupButton(GUI_BUTTON_YES, NULL);

    IupSetCallback(
        yesHandle,
        "ACTION",
        (Icallback)p_gStFlg(&overwrite, true, IUP_CLOSE));

    noHandle = IupButton(GUI_BUTTON_NO, NULL);
    IupSetCallback(noHandle, "ACTION", (Icallback)p_gExit);

    dialog = IupDialog(
        IupVbox(
            message, IupHbox(
                yesHandle, noHandle, NULL), NULL));

    IupPopup(dialog, IUP_CENTER, IUP_CENTER);

    IupMainLoop();

    return overwrite;
}

#endif
