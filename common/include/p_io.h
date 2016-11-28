/* fileIO.h - includes files and defines things needed for file IO

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

READBYTE(file) - reads a byte from file
WRITEBYTE(file, obyte) - writes to file with the given byte

*/

#ifndef P_IO_H
#include <p_common.h>

#define READBYTE(file) fgetc(file)
#define WRITEBYTE(obyte, file) fputc(obyte, file)

#define P_IO_H NULL
#endif
