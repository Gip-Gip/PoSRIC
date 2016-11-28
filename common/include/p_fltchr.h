/* p_fltchr.h - includes things and defines macros needed for p_fltchr checksum
                stuff

ENUMS:

TYPEDEFS:

DEFINITIONS:

P_FIA - the initial value for p_fltchr A
P_FIB - the initial value for p_fltchr B
P_FINIT - the initial value for any p_fltchr-type variable

MACROS:

P_FWRT(file, checksum) - write the checksum to the file
P_FINITF(file) - initializes the p_fltchr from an existing checksum
P_FVALID(checksum) - returns true if the checksum is valid
P_FINC(value, checksum) - adds the value from the checksum
P_FDEC(value, checksum) - removes a value from the checksum


*/

#ifndef P_FLTCHR_H
#include <p_io.h>

#define P_FIA 1
#define P_FIB 0

#define P_FWRT(checksum, file) (WRITEBYTE(checksum.a, file), \
                                WRITEBYTE(checksum.b, file))
#define P_FINIT(checksum) (checksum.a = P_FIA, checksum.b = P_FIB)
#define P_FINITF(checksum, file) (checksum.a = READBYTE(file), \
                                  checksum.b = READBYTE(file))
#define P_FVALID(checksum) (checksum.b == P_FIB && checksum.a == P_FIA)
#define P_FDEC(value, checksum) ((checksum.b -= (checksum.a)), \
                                 (checksum.a -= value))
#define P_FINC(value, checksum) (checksum.b += (checksum.a += value))

#define P_FLTCHR_H NULL
#endif
