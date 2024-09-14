#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include "prompt.h"
#include "parser.h"

#define RUNNING -1
#define TERMINATED 0
#define ERROR 1


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



int loop() {
    int status = RUNNING;
    while(status == RUNNING) {
        prompt();
        char *line;
        readline(&line);
        status = parseline(line);
        free(line);
        if(status == TERMINATED) {
            continue;
        }
    }
    return status;
}

int main() {
    int status = loop();
    return status;
}
