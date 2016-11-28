/* messages.h - defines the messages used

ENUMS:

TYPEDEFS:

DEFINITIONS:

MACROS:

*/

#ifndef MESSAGES_H
#include <p_common.h>

extern char **gargv;

#define PROGNAME gargv[ZERO]

#define MSG_SPLASH \
"\nPoSRIC I.MMXVI rev. 4\n\
Run \"%s -h\" to get help, \"%< -L\" to get legal info\n\n", PROGNAME
#define MSG_LICENSE "\n\
Copyright (c) 2016, Charles Thompson <chmithbiz@gmail.com>\n\
Permission to use, copy, modify, and/or distribute this software for any \n\
purpose with or without fee is hereby granted, provided that the above\n\
copyright notice and this permission notice appear in all copies.\n\
\n\
THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL WARRANTIES\n\
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF\n\
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY\n\
SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER\n\
RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF\n\
CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN\n\
CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.\n\n"

#define MSG_PERROR "ERROR"
#define MSG_ANOTSET "ERROR: Archive not set!\n"
#define MSG_TNOTSET "ERROR: Temporary file not set!\n"
#define MSG_ATNOTSET \
    "ERROR: Both the archive and the temporary file are not set!\n"
#define MSG_FILEEXISTS(file) "ERROR: \"%s\" already exists!\n", file
#define MSG_ECHO "%s\n", params
#define MSG_BADCOMM "ERROR: Unknown command \"%s\"\n", comm
#define MSG_BADRIDGE1 "ERROR: File ends before ridge ends!\n"
#define MSG_BADFLETCHER "ERROR: Invalid fletcher checksum!\n"
#define MSG_BADSIG "ERROR: Archive has a bad signature!"

#define MESSAGES_H NULL
#endif
