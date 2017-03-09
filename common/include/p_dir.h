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
#include <p_messag.h>

extern dirTree p_getRdgDT;

#define P_DTCURR(dt) dt.dirs[dt.dirCount - ONE]

#define P_DTINIT(dt) \
    ((dt.dirs = calloc(STRALLOC, sizeof(string))) && \
    (dt.freeList = calloc(STRALLOC, sizeof(bool))) && !(dt.dirCount = ZERO) && \
    ((dt.freeList[dt.dirCount] = false) | true))

#define P_DTADD(dt, dir, freeable) { \
    dt.dirs = realloc(dt.dirs, sizeof(string) * (dt.dirCount += ONE)); \
    dt.freeList = realloc(dt.freeList, sizeof(bool) * (dt.dirCount)); \
    dt.dirs[dt.dirCount - ONE] = dir; \
    dt.freeList[dt.dirCount - ONE] = freeable;}

#define P_DTREM(dt, erret) { \
    if(dt.freeList[dt.dirCount -= (dt.dirCount ? ONE : ZERO)]) \
        free(dt.dirs[dt.dirCount]); \
    if(dt.dirCount == 0) \
    { \
        p_print(MSG_ROOTPARENT); \
        return erret; \
    } \
    dt.dirs = realloc( \
        dt.dirs, sizeof(string) * (dt.dirCount ? dt.dirCount : ONE)); \
    dt.freeList = realloc( \
        dt.freeList, sizeof(string) * (dt.dirCount ? dt.dirCount : ONE));}

#define P_DTCMP(dt1, dt2) (dt1.dirCount == dt2.dirCount && \
    (dt1.dirCount && p_msCmpS(dt1.dirs, dt2.dirs, dt1.dirCount)))

#define P_DTCOPY(dest, src) { \
    dest.dirCount = src.dirCount; \
    dest.freeList = calloc(src.dirCount, sizeof(bool)); \
    dest.dirs = calloc(src.dirCount, sizeof(string)); \
    memcpy(dest.freeList, src.freeList, sizeof(bool) * src.dirCount); \
    while(dest.dirCount --) \
    { \
        dest.dirs[dest.dirCount] = calloc( \
            strlen(src.dirs[dest.dirCount]) + STRALLOC, sizeof(character)); \
        strcpy(dest.dirs[dest.dirCount], src.dirs[dest.dirCount]); \
        dest.freeList[dest.dirCount] = true; \
    } \
    dest.dirCount = src.dirCount; }

#define P_DTDINIT(dt) {while(dt.dirCount --) \
    if(dt.freeList[dt.dirCount]) free(dt.dirs[dt.dirCount]); \
    free(dt.dirs), free(dt.freeList), dt.dirs = NULL;}

#define P_GDTINIT(dir, free) \
    P_DTINIT(p_getRdgDT); \
    P_DTADD(p_getRdgDT, dir, free);

#define P_DIR_H NULL
#endif
