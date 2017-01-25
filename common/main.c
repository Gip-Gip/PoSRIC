/* main - interprets and calls things

ARGUMENTS:

int argc - the amount of command-line variables provided
char **argv - the command-line arguments

VARIABLES:

string archiveName - the name of the archive in use
string tmpName - the name of the temporary file in use
string name - the name of the in-archive file in use
bool verbose - global verbose boolean
bool overwrite - global overwrite boolean
bool noScript - if set, there will be no command interpretation
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
retVal ret - used for storing errors

*/

#include <main.h>

string archiveName = NULL, tmpName = NULL, name = NULL;
bool verbose = false, overwrite = false, noScript = false, argArchive = false,
argTmp = false, argName = false;
FILE *logFile = NULL, *p_stdin;
char **gargv;
natural buffSz = 1;

int main(int argc, char **argv)
{
    natural argn = ZERO;
    command comID;
    string comm = NULL, params = NULL;
    bool freeParams = true;
    retVal ret = none;
    dirTree currDir;

    p_stdin = stdin;
    gargv = argv;

    p_print(MSG_SPLASH);

    if(!P_FTINIT() || !P_FTADD(FUNCNAME) || !P_DTINIT(currDir))
    {
        perror(MSG_PERROR);
        return errno;
    }

    P_PREARGS();

/*=============================================================================:
:------------------------------------------------------------------------------:
:---------------------------ARGUMENT--INTERPRETATION---------------------------:
:------------------------------------------------------------------------------:
:=============================================================================*/
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

            case(arg_noScript):
                noScript = true;
                break;

            case(arg_overwrite):
                overwrite = true;
                break;

            case(arg_verbose):
                verbose = true;
                break;

            case(arg_format):
                if(archiveName) ret = p_format(archiveName, overwrite);

                else p_print(MSG_ANOTSET);
                break;

            case(arg_list):
                if(archiveName) ret = p_list(archiveName);

                else p_print(MSG_ANOTSET);
                break;

            case(arg_exitDir):
                P_DTREM(currDir, err_rootParent);
                break;

            case(arg_logFile): case(arg_script): case(arg_buffSz):
            case(arg_archive): case(arg_tmpFile): case(arg_quickAdd):
            case(arg_quickGet): case(arg_addDir): case(arg_quickRm):
            case(arg_useDir):
                break;

            default:
                switch(p_getArg(argv[argn - 1]))
                {
                    case(arg_archive):
                        argArchive = true;
                        if(archiveName) P_DTREM(currDir, err_rootParent);
                        archiveName = argv[argn];
                        P_DTADD(currDir, archiveName, false);
                        break;

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

                    case(arg_useDir):
                        P_DTADD(currDir, argv[argn], false);
                        break;

                    case(arg_quickAdd):
                        if(archiveName && tmpName) ret = p_addFd(archiveName,
                            tmpName, argv[argn], argv[argn], overwrite, buffSz,
                            currDir);

                        if(!archiveName) p_print(MSG_ANOTSET);
                        if(!tmpName) p_print(MSG_TNOTSET);
                        break;

                    case(arg_quickGet):
                        if(archiveName && tmpName) ret =
                            p_getFd(archiveName, argv[argn], argv[argn],
                                overwrite);

                        if(!archiveName) p_print(MSG_ANOTSET);
                        if(!tmpName) p_print(MSG_TNOTSET);
                        break;

                    case(arg_quickRm):
                        if(archiveName && tmpName) ret = p_rmFile(
                            archiveName, tmpName, argv[argn], overwrite, currDir);

                        if(!archiveName) p_print(MSG_ANOTSET);
                        if(!tmpName) p_print(MSG_TNOTSET);
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

                    case(arg_tmpFile):
                        argTmp = true;
                        tmpName = argv[argn];
                        break;

                    default:
                        p_print(MSG_BADARG);
                        break;

                }
                break;
        }
    }

    /* I commonly add -n to the preargs list, and I expect others to do the
       same. To make the S in PoSRIC not totally useless, when including a
       script manually disable the noScript option */

    if(p_stdin == stdin && noScript)
    {
        P_FREEALL();
        return none;
    }

/*=============================================================================:
:------------------------------------------------------------------------------:
:----------------------------COMMAND-INTERPRETATION----------------------------:
:------------------------------------------------------------------------------:
:=============================================================================*/
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

            case(comm_exitDir):
                P_DTREM(currDir, err_rootParent);
                break;

            case(comm_echo):
                p_print(MSG_ECHO);
                break;

            case(comm_use):
                if(archiveName)
                {
                    if(!argArchive) free(archiveName);
                    P_DTREM(currDir, err_rootParent);
                }

                argArchive = false;

                archiveName = params;
                P_DTADD(currDir, params, false);

                freeParams = false;
                break;
            case(comm_useDir):
                P_DTADD(currDir, params, true);
                freeParams = false;
                break;

            case(comm_useName):
                if(name && !argName) free(name);

                argName = false;

                name = params;
                freeParams = false;
                break;

            case(comm_tmp):
                if(tmpName && !argTmp) free(tmpName);

                argTmp = false;

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
                if(archiveName && tmpName && name)
                    ret = p_getFd(archiveName, params, name, overwrite);

                if(!archiveName) p_print(MSG_ANOTSET);
                if(!tmpName) p_print(MSG_TNOTSET);
                if(!name) p_print(MSG_NNOTSET);
                break;

            case(comm_addDr):
                if(archiveName && tmpName)
                    ret = p_addDr(archiveName, tmpName, params, overwrite,
                        currDir);

                if(!archiveName) p_print(MSG_ANOTSET);
                if(!tmpName) p_print(MSG_TNOTSET);
                break;

            case(comm_addFn):
                if(archiveName && tmpName)
                    ret = p_addFn(archiveName, tmpName, params, overwrite,
                        currDir);

                if(!archiveName) p_print(MSG_ANOTSET);
                if(!tmpName) p_print(MSG_TNOTSET);
                break;

            case(comm_addFd):
                if(archiveName && tmpName && name)
                    ret = p_addFd(archiveName, tmpName, params, name, overwrite,
                        buffSz, currDir);

                if(!archiveName) p_print(MSG_ANOTSET);
                if(!tmpName) p_print(MSG_TNOTSET);
                if(!name) p_print(MSG_NNOTSET);
                break;

            case(comm_rmFile):
                if(archiveName && tmpName)
                    ret = p_rmFile(
                        archiveName, tmpName, params, overwrite, currDir);

                if(!archiveName) p_print(MSG_ANOTSET);
                if(!tmpName) p_print(MSG_TNOTSET);
                break;

            case(comm_quickAdd):
                if(archiveName && tmpName)
                    ret = p_addFd(archiveName, tmpName, params, params,
                        overwrite, buffSz, currDir);

                if(!archiveName) p_print(MSG_ANOTSET);
                if(!tmpName) p_print(MSG_TNOTSET);
                break;

            case(comm_quickGet):
                if(archiveName && tmpName)
                    ret = p_getFd(archiveName, params, params, overwrite);

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

/*=============================================================================:
:------------------------------------------------------------------------------:
:-------------------------------DEINITIALIZATION-------------------------------:
:------------------------------------------------------------------------------:
:=============================================================================*/

    if(!params)
    {
        perror(MSG_PERROR);
        P_FREEALL();
        return errno;
    }

    /* Free all memory to make valgrind happy :) */

    P_FREEALL();

    return none;
}
