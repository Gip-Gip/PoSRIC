/* messages.h - defines the messages used

ENUMS:

TYPEDEFS:

DEFINITIONS:

MSG_SPLASH - the splash message that is displayed when posric starts
MSG_AUTHORS - a list of people that contributed to posric
MSG_LICENSE - the license that posric is under
MSG_PERROR - the text printed with perror
MSG_BADARG - an error that notifies the user of an invalid command line argument
MSG_ANOTSET - tells that the archive is not set
MSG_TNOTSET - tells that the temporary file is not set
MSG_ATNOTSET - tells that both the archive and the temporary file are not set
MSG_FILEEXISTS - tells that a file already exists
MSG_NAMEEXISTS - ditto, except with in-archive names
MSG_NAMEDEXISTS - tells that an in-archive file wasn't found
MSG_NAMEDUPED - tells that an in-archive file was duplicated somehow
MSG_FILEFOUND1 & MSG_FILEFOUND2 - used when listing files found in an archive
MSG_ECHO - the format used when the echo command is executed
MSG_BADCOMM - tells that a bad command has been entered
MSG_BADRIDGE1 - one of the possible messages for a bad ridge
MSG_BADFLETCHER - tells that a bad fletcher checksum has been encountered
MSG_BADSIG - tells that the archive has a bad signature
MSG_EMPTYFILE - tells that the file didn't have any useful data in it

MACROS:

MSG_ERROR(MSG) - formats the given message to the standard error layout
MSG_INFO(MSG) - formats the given message to the standard info layout
MSG_INFON(MSG) - ditto, except without a newline at the end

*/

#ifndef MESSAGES_H
#include <p_common.h>

extern char **gargv;

#ifdef BASHCOLOR
#define MSG_ERROR(MSG) \
    ("%v%s(%n)%v\033[1;31mERROR: \033[0;31m" MSG "\033[0m\n"),P_FT, __LINE__
#define MSG_INFO(MSG) \
    ("%v%s(%n)%v\033[1;37mINFO: \033[0;37m" MSG "\033[0m\n"), P_FT, __LINE__
#define MSG_INFON(MSG) \
    ("%v%s(%n)%v\033[1;37mINFO: \033[0;37m" MSG "\033[0m"), P_FT, __LINE__
#else
#define MSG_ERROR(MSG) ("%v%s(%n)%vERROR: " MSG "\n"), P_FT, __LINE__
#define MSG_INFO(MSG) ("%v%s(%n)%vINFO: " MSG "\n"), P_FT, __LINE__
#define MSG_INFON(MSG) ("%v%s(%n)%vINFO: " MSG), P_FT, __LINE__
#endif

#ifndef PROGNAME
#define PROGNAME gargv[ZERO]
#endif

#define MSG_SPLASH \
"\nPoSRIC IIV.IIV.MMXVII Revision 3\n\
Run \"%s -h\" to get help,\n\
\"%< -L\" to get legal info, and\n\
\"%< -A\" to get the list of authors\n\n", PROGNAME

#define MSG_AUTHORS "\n\
AUTHORS:\n\
Charles \"Gip-Gip\" Thompson - Project owner\n\
hogg2016(reddit) - Bug feedback(Fixed an issue on DOS)\n\n"

#define MSG_LICENSE "\n\
Copyright (c) 2016, Charles Thompson <chmithbiz@gmail.com>\n\n\
Permission to use, copy, modify, and/or distribute this software for any \n\
purpose with or without fee is hereby granted, provided that the above\n\
copyright notice and this permission notice appear in all copies.\n\n\
THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL WARRANTIES\n\
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF\n\
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY\n\
SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER\n\
RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF\n\
CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN\n\
CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.\n\n"

#define MSG_PERROR P_FT
#define MSG_BADARG MSG_ERROR("Unknown argument \"%s\"!"), argv[argn]
#define MSG_ANOTSET MSG_ERROR("Archive not set!")
#define MSG_TNOTSET MSG_ERROR("Temporary file not set!")
#define MSG_NNOTSET MSG_ERROR("No name in use!")
#define MSG_FILEEXISTS(file) MSG_ERROR("\"%s\" already exists!"), file
#define MSG_NAMEEXISTS(name) MSG_ERROR("\"%s\" already exists in archive!"), \
    name
#define MSG_DIREXISTS(name) \
    MSG_ERROR("Directory \"%s\" already exists in archive!"), name
#define MSG_NAMEDEXIST(name) MSG_ERROR("\"%s\" doesn't exist in archive!"), \
    name
#define MSG_DIRDEXIST(dt) \
    MSG_ERROR("Directory \"%s\" doesn't exist in archive!"), P_DTCURR(dt)
#define MSG_NAMEDUPED(name) MSG_ERROR("\"%s\" appeared twice in the archive!"),\
    name
#define MSG_FILEFOUND1 "%s\r%#|-", "| ", p_getRdgDT.dirCount - 1
#define MSG_FILEFOUND2 "\n"
#define MSG_ECHO "%v%s%v%s\n", P_FT, params
#define MSG_BADCOMM MSG_ERROR("Unknown command \"%s\"\n"), comm
#define MSG_BADRIDGE1 MSG_ERROR("File ends before ridge ends!\n")
#define MSG_BADFLETCHER MSG_ERROR("Invalid fletcher checksum!\n")
#define MSG_BADSIG MSG_ERROR("Archive has a bad signature!")
#define MSG_EMPTYFILE(name) MSG_ERROR("\"%s\" is an empty file!"), name
#define MSG_ROOTPARENT MSG_ERROR("Root directory lacks a parent!")

#define MESSAGES_H NULL
#endif
