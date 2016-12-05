/* main - interprets arguments and calls things

ARGUMENTS:

VARIABLES:

*/

#include <main.h>

string archiveName = NULL, tmpName = NULL;
bool verbose = false;
bool overwrite = false;
FILE *logFile = NULL, *p_stdin;
char **gargv;

int main(int argc, char **argv)
{
    natural argn = ZERO;
    command comID;
    string comm, params;
    bool freeParams = true;
    retval ret = none;

    p_stdin = stdin;
    gargv = argv;

    p_print(MSG_SPLASH);

    /* Get the command-line arguments */
    while(++argn < argc)
    {
        switch(p_getArg(argv[argn]))
        {
            case(arg_authors):
                p_print(MSG_AUTHORS);
                return err_authorsGiven;

            case(arg_help):
                p_help();
                return err_helpGiven;

            case(arg_license):
                p_print(MSG_LICENSE);
                return err_licenseGiven;

            case(arg_overwrite):
                overwrite = true;
                break;

            case(arg_verbose):
                verbose = true;
                break;

            case(arg_logFile): case(arg_script):
                break;

            default:
                switch(p_getArg(argv[argn - 1]))
                {
                    case(arg_logFile):
                        if(!overwrite && fopen(argv[argn], READMODE))
                        {
                            p_print(MSG_FILEEXISTS(argv[argn]));
                            return err_fileExists;
                        }

                        if(logFile) fclose(logFile);
                        if(!(logFile = fopen(argv[argn], WRITEMODE)))
                        {
                            perror(MSG_PERROR);
                            return errno;
                        }
                        break;

                    case(arg_script):
                        if(p_stdin != stdin) fclose(p_stdin);
                        if(!(p_stdin = fopen(argv[argn], READMODE)))
                        {
                            perror(MSG_PERROR);
                            return errno;
                        }
                        break;

                    default:
                        p_print(MSG_BADARG);
                        break;

                }
                break;
        }
    }

    /* Read the commands from p_stdin */
    while(!feof(p_stdin))
    {
        if(!(params = p_readIn(&comID, &comm)))
        {
            perror(MSG_PERROR);
            if(comm) free(comm);
            return errno;
        }

        switch(comID)
        {
            case(comm_comment):
                break;

            case(comm_exit):
                if(tmpName) free(tmpName);
                if(archiveName) free(archiveName);
                free(params);
                free(comm);
                return none;

            case(comm_giveUp):
                if(ret)
                {
                    p_print(MSG_ECHO);
                    return err_giveUp;
                }
                break;

            case(comm_echo):
                p_print(MSG_ECHO);
                break;

            case(comm_use):
                if(archiveName) free(archiveName);

                archiveName = params;
                freeParams = false;
                break;

            case(comm_tmp):
                if(tmpName) free(tmpName);

                tmpName = params;
                freeParams = false;
                break;

            case(comm_format):
                if(archiveName) ret = p_format(archiveName, overwrite);

                else p_print(MSG_ANOTSET);
                break;

            case(comm_addFn):
                if(archiveName && tmpName)
                    ret = p_addFn(archiveName, tmpName, params, overwrite);

                else if(archiveName) p_print(MSG_TNOTSET);

                else if(tmpName) p_print(MSG_ANOTSET);

                else p_print(MSG_ATNOTSET);
                break;

            default:
                p_print(MSG_BADCOMM);
                ret = err_unknownCommand;
                break;
        }

        if(freeParams) free(params);
        else freeParams = true;

        free(comm);
    }

    /* Free all the memory to make valgrind happy :) */
    if(tmpName) free(tmpName);
    if(archiveName) free(archiveName);

    return none;
}
