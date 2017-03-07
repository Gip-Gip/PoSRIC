/* p_readIn - reads a command from p_stdin and returns the paramiters along with
             the command ID

ARGUMENTS:

command *comID - a pointer to the command ID
string *comm - the pointer to store the command to

VARIABLES:

*/

#include <p_readIn.h>

string p_readIn(command *comID, string *comm)
{
    character usedTerm;
    *comm = p_getStr(p_stdin, COMMDELM, &usedTerm, true);

    *comID = ZERO;

    while(p_comEnt[*comID] != NULL && strcmp(p_comEnt[*comID], *comm))
        ++*comID;

    if(usedTerm != COMMDELM) return calloc(STRALLOC, sizeof(character));

    return p_getStr(p_stdin, PARMDELM, &usedTerm, false);
}
