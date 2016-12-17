/* p_getArg - checks the string to see if it's an argument

ARGUMENTS:

string str - the string being compared

VARIABLES:

natural index - used for going through the argument array

*/

#include <p_getArg.h>

arg p_getArg(string str)
{
    natural index = ZERO;

    while(p_args[index])
    {
        if(!strcmp(p_args[index + ARGS_SHRTDPTH], str) |
           !strcmp(p_args[index + ARGS_LONGDPTH], str))
           return index / ARGS_ENTRYDPTH;

        index += ARGS_ENTRYDPTH;
    }

    return index;
}
