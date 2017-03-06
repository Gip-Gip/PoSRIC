/*

ARGUMENTS:

VARIABLES:

byte p_sig[] - the file signature for a posric file
string p_fncTrk - the function track string

*/

#include <p_string.h>

byte p_sig[P_SIGSZ] = {'e', 'x', 't', 128};

rType p_fileRdgs[] =
{
    rType_fname, rType_fdata, rType_addtime, rType_atime, rType_ctime,
    rType_mtime, rType_foo
};

string p_fncTrk = NULL;
