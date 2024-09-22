#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
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

void waitallchildren(int childc) {
    for(int i = 0 ; i < childc ; i++) {
        wait(NULL);
    } 
}

int main() {
    while(1) {
        prompt();
        char *line;
        readline(&line);
        command_t **commands;
        int comc = parse(line, &commands);
        free(line);
        exec(comc, commands);
        waitallchildren(comc);
    }
    return 0;
}
