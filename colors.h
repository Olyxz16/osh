// https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
#define _COLRED_     "\x1b[31m"
#define _COLRESET_   "\x1b[0m"

#define fontred()    fputs("\x1b[31m", stderr)
#define fontreset()  fputs("\x1b[0m", stderr)
