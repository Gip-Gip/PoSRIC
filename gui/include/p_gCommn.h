/* p_gCommn.h - includes files needed by most GUI source files

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_GCOMMN_H

#include <p_gTypes.h>

extern string archiveName;
extern Ihandle *statusBar;
extern string p_guiErrors[];
extern void p_gError(retVal);
extern gCallback p_gExit(void);
extern gCallback p_gFormt(void);
extern gCallback p_gOpenA(void);
extern bool p_gOvrWd(void);

#define P_GCOMMN_H NULL
#endif
