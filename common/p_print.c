/* p_print - project-wide logging function

ARGUMENTS:

char *format - the format of the message being printed

VARIABLES:

va_list arglist - the variable-argument list
string history - the previous p_print
bool freeHistory - if set, history will be freed
character chr[] - the buffer used for storing single characters
natural num - used for natural conversions

*/

#include <p_print.h>

void p_print(string format, ...)
{
    va_list arglist;
    string history = NULL;
    bool freeHistory = false, verboseActive = false;
    character chr[] = {0, 0};
    natural num = 1;

    va_start(arglist, format);

    while(*format)
    {
        if(*format == PRINT_STYLDELM) switch(*(++format))
        {
            case(PRINT_STYLSTR):
                if(freeHistory)
                {
                    freeHistory = false;
                    free(history);
                }

                if(verbose || !verboseActive)
                    p_print(history = va_arg(arglist, string));
                break;
            case(PRINT_STYLNATR):
                if(freeHistory) free(history);

                num = va_arg(arglist, natural);
                history =
                    calloc((num?floor(log10(num)):STRALLOC) +
                    (STRALLOC * PRINT_NCORR), sizeof(character));
                sprintf(history, F_NATURAL, num);
                if(verbose || !verboseActive) p_print(history);

                freeHistory = true;
                break;
            case(PRINT_STYLCHAR):
                if(freeHistory)
                {
                    freeHistory = false;
                    free(history);
                }

                /* Since va promotes chars to ints... */
                *chr = va_arg(arglist, int);

                history = chr;
                if(verbose || !verboseActive) p_print(history);
                break;
            case(PRINT_STYLVERB):
                verboseActive = !verboseActive;
                break;
            case(PRINT_STYLPREV):
                if((verbose || !verboseActive) && history) p_print(history);
                break;
        }

        else if(verbose || !verboseActive)
            if(fputc(*format, stderr) != *format ||
                (logFile && fputc(*format, logFile) != *format))

                    perror(MSG_PERROR);

        format ++;
    }
}

