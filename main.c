#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RUNNING -1
#define TERMINATED 0
#define ERROR 1


int readline(char **line) {
    size_t n = 1024;
    *line = malloc(n * sizeof(char));
    int len = getline(line, &n, stdin);
    // Remove trailing newline
    char *copy = malloc(n * sizeof(char));
    strncpy(copy, *line, len-1);
    *line = copy;
    return len-1;
}

int parseline(char *line) {
    if(strcmp(line, "exit") == 0) {
        return TERMINATED;
    }
    return RUNNING;
}

int loop(const char* prompt) {
    int status = RUNNING;
    while(status == RUNNING) {
        fputs(prompt, stderr);
        char *line = "";
        readline(&line);
        status = parseline(line);
        if(status == TERMINATED) {
            return TERMINATED;
        }
    }
    return status;
}

int main() {
    const char* prompt = "osh> ";
    int status = loop(prompt);
    return status;
}
