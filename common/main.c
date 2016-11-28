/* main - interprets arguments and calls things

ARGUMENTS:

VARIABLES:

*/

#include <main.h>

extern string p_readIn();

string archiveName = NULL, tmpName = NULL;
bool verbose = false;
bool overwrite = false;
FILE *logFile = NULL;
char **gargv;

int main(int argc, char **argv)
{
    natural argn = ZERO;
    command comID;
    string comm, params;
    bool freeParams = false;
    retval ret = none;

    gargv = argv;

    while(++argn < argc)
    {
        switch(p_getArg(argv[argn]))
        {
            case(arg_help):
                p_help();
                return err_helpGiven;
                break;

            case(arg_license):
                p_print(MSG_LICENSE);
                return err_licenseGiven;
                break;

            case(arg_overwrite):
                overwrite = true;
                break;

            case(arg_verbose):
                verbose = true;
                break;

            case(arg_logFile):
                break;

            default:
                switch(p_getArg(argv[argn - 1]))
                {
                    case(arg_logFile):
                        if(!overwrite && (logFile = fopen(argv[argn], "rb")))
                        {
                            p_print(MSG_FILEEXISTS(argv[argn]));
                            return err_fileExists;
                        }

                        logFile = fopen(argv[argn], "wb");
                        break;
                }
                break;
        }
    }

    while(!feof(stdin))
    {
        if(!(params = p_readIn(&comID, &comm)))
        {
            perror(MSG_PERROR);
            return errno;
        }

        switch(comID)
        {
            case(comm_comment):
                break;

            case(comm_exit):
                return none;
                break;

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
                    ret = p_addFn(archiveName, tmpName, params);

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

    return none;
}
