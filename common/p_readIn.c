/* p_readIn - reads a command from stdin and returns the paramiters along with
             the command ID

ARGUMENTS:

command *comID - a pointer to the command ID

VARIABLES:

*/

#include <p_readIn.h>

string p_readIn(command *comID, string *comm)
{
    *comm = p_getStr(stdin, COMMDELM, true);

    *comID = ZERO;

    while(p_comEnt[*comID] != NULL && strcmp(p_comEnt[*comID], *comm))
        ++*comID;

    return p_getStr(stdin, PARMDELM, false);
}
