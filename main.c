#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include "prompt.h"
#include "parser.h"
#include "exec.h"


int readline(char **line) {
    size_t n = 1024;
    *line = (char *)malloc(n * sizeof(char));
    int len = getline(line, &n, stdin);
    // Remove trailing newline
    char *cp = *line;
    cp[len-1] = '\0';
    *line = cp;
    return len-1;
}

int main() {
    while(1) {
        prompt();
        char *line;
        readline(&line);
        char **argv;
        int argc = parseline(line, &argv);
        free(line);
        exec(argc, argv);
    }
    return 0;
}
