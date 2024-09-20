// https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
#define _RD          "\x1b[31m"
#define _GN          "\x1b[32m"
#define _BL          "\x1b[34m"
#define _0           "\x1b[0m"

#define fontred()    fputs("\x1b[31m", stderr)
#define fontreset()  fputs("\x1b[0m", stderr)
