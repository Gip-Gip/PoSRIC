/* p_oCommn.h - includes OS-dependant files for OS-dependant code

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_OCOMMN_H

#include <p_common.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <p_dir.h>

string p_oGetDf(DIR *);
string p_oGetDd(DIR *);

#define P_ODIRDELEM "/"

#define P_OCOMMN_H NULL
#endif
