/* p_dir.h - includes files and defines things needed for directory tracking

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

P_DTINIT - initializes a dirTree
P_DTADD - adds a directory to a dirTree
P_DTREM - removes a directory from a dirTree
P_DTCMP - compares two dirTrees
P_DTDINIT - de-initializes a dirTree
P_GDTINIT - initializes the global dirTree to the given directory

*/

#ifndef P_DIR_H
#include <p_common.h>

extern dirTree p_getRdgDT;

#define P_DTCURR(dt) dt.dirs[dt.dirCount - ONE]

#define P_DTINIT(dt) \
    ((dt.dirs = calloc(STRALLOC, sizeof(string))) && !(dt.dirCount = ZERO))

#define P_DTADD(dt, dir) \
    ((dt.dirs = realloc(dt.dirs, sizeof(string) * (dt.dirCount += ONE))) && \
    (dt.dirs[dt.dirCount - ONE] = dir))

#define P_DTREM(dt) \
    (dt.dirs = realloc( \
        dt.dirs, sizeof(string) * (dt.dirCount -= ONE ? dt.dirCount : ONE)))

#define P_DTCMP(dt1, dt2) (dt1.dirCount == dt2.dirCount && \
    (!dt1.dirCount || p_msCmpS(dt1.dirs, dt2.dirs, dt1.dirCount)))

#define P_DTDINIT(dt) (free(dt.dirs), dt.dirs = NULL)

#define P_GDTINIT(dir) (P_DTINIT(p_getRdgDT) && P_DTADD(p_getRdgDT, dir))

#define P_DIR_H NULL
#endif
