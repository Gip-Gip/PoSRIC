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
#include <time.h>
#include <p_fncTrk.h>

#define P_INITUNIXT(var) {\
    var.tm_sec = var.tm_min = var.tm_hour = var.tm_mon = var.tm_yday =\
    var.tm_isdst = ZERO, var.tm_year = 70, var.tm_mday = 1, var.tm_wday = 4;}

extern FILE *p_stdin;
extern bool p_dontRecDir;
extern rType p_fileRdgs[];

extern int main(int, char **);
extern string p_dToS(byte *, natural, bool, retVal *);
extern bool p_flExst(string);
extern arg p_getArg(string);
extern string p_getStr(FILE *, character, character *, bool);
extern void p_help( void );
extern bool p_msCmpS(string *, string *, natural);
extern natural p_msCrAa(rType, rType *);
extern void p_print(string, ...);
extern string p_readIn(command *, string *);
extern string p_strapp(string, string, bool, bool);
extern string p_strcut(string, natural, bool);
extern bool p_cmpDta(byte *, natural, FILE *);
extern byte *p_read(FILE *, retVal *, natural *);
extern byte *p_getRdg(FILE *, rType *);
extern retVal p_list(string);
extern retVal p_stat(string, string, dirTree);
extern retVal p_getFd(string, string, string, dirTree, bool);
extern retVal p_sCaC(FILE *, FILE *);
extern retVal p_skpDta(FILE *, bool);
extern retVal p_skpDtI(FILE *, rType, bool);
extern retVal p_skpDtU(FILE *, rType, bool);
extern retVal p_skpDtF(FILE *, string, dirTree);
extern retVal p_skpDUU(FILE *, rType, rType, bool);
extern retVal p_addDr(string, string, string, bool, dirTree);
extern retVal p_addFn(string, string, string, bool, dirTree);
extern retVal p_addFd(string, string, string, string, bool, natural, dirTree);
extern retVal p_cpyExc(FILE *, FILE *, string, rType, retVal *, dirTree);
extern retVal p_copy(FILE *, FILE *);
extern retVal p_format(string, bool);
extern retVal p_rmFile(string, string, string, bool, dirTree);
extern retVal p_write(byte *, natural, FILE *);
extern retVal p_wrtRdg(FILE *, rType, byte *);
extern ssln p_t2ut(time_t);
extern ssln p_ut2lt(ssln);
extern retVal p_oRecD(string, string, string, bool, natural, dirTree);

#define P_COMMON_H NULL
#endif
