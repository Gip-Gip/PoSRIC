/* main - interprets arguments and calls things

ARGUMENTS:

int argc - the amount of command-line variables provided
char **argv - the command-line arguments

VARIABLES:

string archiveName - the name of the archive in use
string tmpName - the name of the temporary file in use
string name - the name of the in-archive file in use
bool verbose - global verbose boolean
bool overwrite - global overwrite boolean
FILE *logFile - the log file pointer
FILE *p_stdin - project-wide stdin substitute
char **gargv - global argv
natural buffSz - the size of the buffer in multiples of 128
natural argn - index used for going through the command line arguments
command comID - variable used for storing the command ID
string comm - variable used for storing the actual command typed
string params - the command parameters
bool freeParams - set during the process of command interpretation; if set
                  params will be freed
retval ret - used for storing errors

*/

#include <main.h>

string archiveName = NULL, tmpName = NULL, name = NULL;
bool verbose = false, overwrite = false;
FILE *logFile = NULL, *p_stdin;
char **gargv;
natural buffSz = 1;

int main(int argc, char **argv)
{
    natural argn = ZERO;
    command comID;
    string comm = NULL, params = NULL;
    bool freeParams = true;
    retval ret = none;

    p_stdin = stdin;
    gargv = argv;

    p_print(MSG_SPLASH);

    if(!P_FTINIT() || !P_FTADD(FUNCNAME))
    {
        perror(MSG_PERROR);
        return errno;
    }

    /* Get the command-line arguments */
    while(++argn < argc)
    {
        switch(p_getArg(argv[argn]))
        {
            case(arg_authors):
                p_print(MSG_AUTHORS);
                P_FREEALL();
                return err_authorsGiven;

            case(arg_help):
                p_help();
                P_FREEALL();
                return err_helpGiven;

            case(arg_license):
                p_print(MSG_LICENSE);
                P_FREEALL();
                return err_licenseGiven;

            case(arg_overwrite):
                overwrite = true;
                break;

            case(arg_verbose):
                verbose = true;
                break;

            case(arg_logFile): case(arg_script): case(arg_buffSz):
                break;

            default:
                switch(p_getArg(argv[argn - 1]))
                {
                    case(arg_buffSz):
                        buffSz = atoi(argv[argn]);
                        break;
                    case(arg_logFile):
                        if(!overwrite && fopen(argv[argn], READMODE))
                        {
                            p_print(MSG_FILEEXISTS(argv[argn]));
                            P_FREEALL();
                            return err_fileExists;
                        }

                        if(logFile) fclose(logFile);
                        if(!(logFile = fopen(argv[argn], WRITEMODE)))
                        {
                            perror(MSG_PERROR);
                            P_FREEALL();
                            return errno;
                        }
                        break;

                    case(arg_script):
                        if(p_stdin != stdin) fclose(p_stdin);
                        if(!(p_stdin = fopen(argv[argn], READMODE)))
                        {
                            perror(MSG_PERROR);
                            P_FREEALL();
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
    while((params = p_readIn(&comID, &comm)) && !feof(p_stdin))
    {
        if(!comm)
        {
            perror(MSG_PERROR);
            return errno;
        }

        switch(comID)
        {
            case(comm_comment):
                break;

            case(comm_giveUp):
                if(ret)
                {
                    p_print(MSG_ECHO);
                    P_FREEALL();
                    return ret;
                }
                break;

            case(comm_exit):
                P_FREEALL();
                return none;

            case(comm_echo):
                p_print(MSG_ECHO);
                break;

            case(comm_use):
                if(archiveName) free(archiveName);

                archiveName = params;
                freeParams = false;
                break;

            case(comm_useName):
                if(name) free(name);

                name = params;
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

            case(comm_list):
                if(archiveName) ret = p_list(archiveName);

                else p_print(MSG_ANOTSET);
                break;

            case(comm_getFd):
                if(archiveName && tmpName)
                    ret = p_getFd(archiveName, params, name, overwrite);

                if(!archiveName) p_print(MSG_ANOTSET);
                if(!tmpName) p_print(MSG_TNOTSET);
                if(!name) p_print(MSG_NNOTSET);
                break;

            case(comm_addFn):
                if(archiveName && tmpName && name)
                    ret = p_addFn(archiveName, tmpName, params, overwrite);

                if(!archiveName) p_print(MSG_ANOTSET);
                if(!tmpName) p_print(MSG_TNOTSET);
                break;

            case(comm_addFd):
                if(archiveName && tmpName && name)
                    ret = p_addFd(archiveName, tmpName, params, name, overwrite,
                    buffSz);

                if(!archiveName) p_print(MSG_ANOTSET);
                if(!tmpName) p_print(MSG_TNOTSET);
                if(!name) p_print(MSG_NNOTSET);
                break;

            case(comm_rmFile):
                if(archiveName && tmpName)
                    ret = p_rmFile(archiveName, tmpName, params, overwrite);

                if(!archiveName) p_print(MSG_ANOTSET);
                if(!tmpName) p_print(MSG_TNOTSET);
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

    if(!params)
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    /* Free all the memory to make valgrind happy :) */
    P_FREEALL();

    return none;
}
