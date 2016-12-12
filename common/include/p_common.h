/* p_common.h - includes things commonly needed and provides prototypes for all
                functions in the project

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef P_COMMON_H
#include <stdio.h>
#include <errno.h>
#include <p_fncTrk.h>

extern FILE *p_stdin;

extern int main(int, char **);
extern arg p_getArg(string);
extern string p_getStr(FILE *, character, bool);
extern void p_help( void );
extern void p_print(string, ...);
extern string p_readIn(command *, string *);
extern string p_strapp(string, string, bool, bool);
extern string p_strcut(string, natural, bool);
extern bool p_cmpDta(byte *, natural, FILE *);
extern byte *p_getRdg(FILE *, rtype *);
extern retval p_sCaC(FILE *, FILE *);
extern retval p_skpDta(FILE *);
extern retval p_skpDtU(FILE *, rtype);
extern retval p_addFn(string, string, string, bool);
extern retval p_addFd(string, string, string, string, bool, natural);
extern retval p_cpyExc(FILE *, FILE *, string, retval *);
extern retval p_format(string, bool);
extern retval p_rmFile(string, string, string, bool);
extern retval p_write(byte *, natural, FILE *);
extern retval p_wrtRdg(FILE *, rtype, byte *);

#define P_COMMON_H NULL
#endif
