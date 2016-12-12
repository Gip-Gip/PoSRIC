/* messages.h - defines the messages used

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef MESSAGES_H
#include <p_common.h>

extern char **gargv;

#ifdef BASHCOLOR
#define MSG_ERROR(MSG) ("%v%s%v\033[1;31mERROR:\033[0;31m " MSG "\033[0m"), P_FT
#else
#define MSG_ERROR(MSG) ("%v%s%vERROR:" MSG), P_FT
#endif

#define PROGNAME gargv[ZERO]

#define MSG_SPLASH \
"\nPoSRIC I.MMXVI rev. 12\n\
Run \"%s -h\" to get help,\n\
\"%< -L\" to get legal info, and\n\
\"%< -a\" to get the list of authors\n\n", PROGNAME

#define MSG_AUTHORS "\n\
AUTHORS:\n\
Charles \"Gip-Gip\" Thompson - Project owner\n\
hogg2016(reddit) - Debugger\n\n"

#define MSG_LICENSE "\n\
Copyright (c) 2016, Charles Thompson <chmithbiz@gmail.com>\n\
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
#define MSG_BADARG MSG_ERROR("Unknown argument \"%s\"!\n"), argv[argn]
#define MSG_ANOTSET MSG_ERROR("Archive not set!\n")
#define MSG_TNOTSET MSG_ERROR("Temporary file not set!\n")
#define MSG_ATNOTSET MSG_ERROR( \
    "Both the archive and the temporary file are not set!\n")
#define MSG_FILEEXISTS(file) MSG_ERROR("\"%s\" already exists!\n"), file
#define MSG_NAMEEXISTS(name) MSG_ERROR("\"%s\" already exists in archive!\n"), \
    name
#define MSG_NAMEDEXIST(name) MSG_ERROR("\"%s\" doesn't exist in archive!\n"), \
    name
#define MSG_NAMEDUPED(name) MSG_ERROR("\"%s\" appeared twice in the archive!"),\
    name
#define MSG_ECHO "%v%s%v%s\n", P_FT, params
#define MSG_BADCOMM MSG_ERROR("Unknown command \"%s\"\n"), comm
#define MSG_BADRIDGE1 MSG_ERROR("File ends before ridge ends!\n")
#define MSG_BADFLETCHER MSG_ERROR("Invalid fletcher checksum!\n")
#define MSG_BADSIG MSG_ERROR("Archive has a bad signature!")

#define MESSAGES_H NULL
#endif
