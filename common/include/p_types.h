/* p_types.h - contains the types used accross the project

ENUMS:

bool - possible boolean states
arg - command line arguments

TYPEDEFS:

natural - natural numbers
real - real numbers(signed)
rational - rational numbers(double)
byte - a single byte
string - a string of characters
character - a single character of a string
bool - flag type
retval - return values

DEFINITIONS:

P_RTYPECORR - the difference between the rtype enum and the actual value

MACROS:

*/

#include <p_defs.h>

#ifndef TYPES_H
typedef unsigned long int natural;
typedef long int real;
typedef double rational;
typedef unsigned char byte;
typedef char character;
typedef character* string;
typedef enum {
    false,
    true,
    neither,
} bool;
typedef enum {
    none,
    err_unknown,
    err_unknownCommand,
    err_giveUp,
    err_fileExists,
    err_helpGiven,
    err_licenseGiven,
    err_authorsGiven,
    err_badSig,
    err_badRidge1,
    err_badFletcher,
    err_nameExists,
    err_nameDexist,
} retval;
typedef enum {
    arg_authors,
    arg_help,
    arg_logFile,
    arg_license,
    arg_script,
    arg_verbose,
    arg_overwrite,
} arg;
typedef enum {
    comm_comment,
    comm_exit,
    comm_giveUp,
    comm_echo,
    comm_use,
    comm_tmp,
    comm_format,
    comm_addFn,
    comm_rmFile,
} command;

typedef enum {
    rtype_fname,
    rtype_fdata,
    rtype_end,
    rtype_null,
} rtype;

typedef struct {
    byte a;
    byte b;
} fletcher;

#define P_RTYPECORR (0xFF - rtype_null)

#define TYPES_H NULL
#endif
