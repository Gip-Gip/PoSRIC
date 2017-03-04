/*

ARGUMENTS:

VARIABLES:

*/

#ifdef IUPGUI

#include <p_gStrng.h>

string p_guiErrors[] = {
    "No Error...", /* none */
    "Unknown Error!", /* err_unknown */
    NULL, /* err_unknownCommand */
    NULL, /* err_giveUp* */
    "File already exists!",
    NULL,
    NULL,
    NULL,
    "Archive has a bad signature!",
    "File ends before ridge ends!",
    "Data doesn't add up!",
    "File already exists in archive",
    "File doesn't exist in archive",
    NULL,
    "Couldn't find (something)",
    "Couldn't find some important stuff!",
    "File doesn't have any data!",
    NULL,
    "Tried to exit root directory!",
    "Directory doesn't exist!",
    "No open archive!",
};

#endif
