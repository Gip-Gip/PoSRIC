/* p_help - prints the p_help message to the screen

ARGUMENTS:

VARIABLES:

natural index - used to go through the argument array

*/

#include <p_help.h>

void p_help( void )
{
    natural index = 0;

    p_print(HELP_USAGE);

    while(p_args[index])
    {
        p_print(HELP_FORMAT);
        index += ARGS_ENTRYDPTH;
    }
}
