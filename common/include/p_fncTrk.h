/* p_fncTrk.h - debugging library for tracking calls

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

P_FTINIT - initializes the global p_fncTrk variable
P_FTADD - adds the function to the p_fncTrk variable
P_FTREM - removes the string at the end

*/

#ifndef P_FNCTRK_H

#include <stdlib.h>
#include <string.h>
#include <p_types.h>

extern string p_fncTrk;

#define P_FNCTRK_FOO "foo"

#define P_FTINIT() (p_fncTrk = calloc(STRALLOC, sizeof(character)))
#define P_FTADD(func) (!p_fncTrk ? P_FNCTRK_FOO : \
                        (p_fncTrk = p_strapp(p_fncTrk, func, true, false)))
#define P_FTREM(func) (!p_fncTrk ? P_FNCTRK_FOO : \
                        (p_fncTrk = p_strcut(p_fncTrk, \
                            strlen(p_fncTrk) - strlen(func), true)))
#define P_FTDINIT() if(p_fncTrk){free(p_fncTrk);p_fncTrk = NULL;}

#define P_FT (p_fncTrk ? p_fncTrk : P_FNCTRK_FOO)

#define P_FNCTRK_H NULL
#endif
