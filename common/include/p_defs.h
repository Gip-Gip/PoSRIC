/* p_defs.h - contains standard definitions

ENUMS:

TYPEDEFS:

DEFINITIONS:

NULL - representation of zero
STRALLOC - the minimum size of a string
F_NATURAL - the formatting for a natural number
P_DCORR - the data ridge correction value
DEFS_H - used to prevent everything from being re-defined

MACROS:

*/

#ifndef P_DEFS_H

#ifndef NULL
#define NULL 0
#endif

#define READMODE "rb"
#define WRITEMODE "wb"
#define ZERO 0
#define INDEXINIT -1
#define STRALLOC 1
#define F_NATURAL "%u"
#define P_DCORR 1
#define P_RMAXSZ 256
#define P_DATA 127
#define P_DEFS_H NULL
#endif
