/* p_types.h - contains the types used accross the project

ENUMS:

bool - possible boolean states
retVal - return values
arg - command line arguments
command - PoSRIC commands
rType - ridge #s

TYPEDEFS:

natural - natural numbers
real - real numbers(signed)
rational - rational numbers(double)
byte - a single byte
string - a string of characters
character - a single character of a string
bool - flag type
retVal - return value
arg - command line argument
command - PoSRIC command
rType - ridge
fletcher - fletcher checksum
dirTree - directory tree

DEFINITIONS:

P_RTYPECORR - the difference between the rType enum and the actual value

MACROS:

*/

#ifndef TYPES_H
#include <p_defs.h>

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
    err_nameDuped,
    err_brkRidge,
    err_notFound,
    err_rNotFound,
    err_emptyFile,
    err_inDir,
    err_rootParent,
    err_dirDexist,
} retVal;

typedef enum {
    arg_archive,
    arg_authors,
    arg_buffSz,
    arg_format,
    arg_help,
    arg_logFile,
    arg_license,
    arg_noScript,
    arg_quickAdd,
    arg_quickGet,
    arg_script,
    arg_list,
    arg_tmpFile,
    arg_verbose,
    arg_overwrite,
} arg;

typedef enum {
    comm_comment,
    comm_exit,
    comm_giveUp,
    comm_echo,
    comm_use,
    comm_useDir,
    comm_useName,
    comm_exitDir,
    comm_tmp,
    comm_format,
    comm_list,
    comm_getFd,
    comm_addDr,
    comm_addFn,
    comm_addFd,
    comm_rmFile,
    comm_quickAdd,
    comm_quickGet,
} command;

typedef enum {
    rType_dend,
    rType_dname,
    rType_fname,
    rType_fdata,
    rType_end,
    rType_null,
    rType_foo,
} rType;

typedef struct {
    byte a;
    byte b;
} fletcher;

typedef struct {
    string *dirs;
    bool *freeList;
    natural dirCount;
} dirTree;

#define P_RTYPECORR (0xFF - rType_null)

#define TYPES_H NULL
#endif
