#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "colors.h"

typedef struct command_pair {
    char *command;
    void (*fun)(int, char **);
} CommandPair;


void exitbi() {
    exit(0);
}

void cd(int argc, char **args) {
    if(argc < 2) {
        return;
    }
    const char *path = args[1];
    int status = chdir(path);
    if(status != 0) {
        fontred();
        perror("cd");
        fontreset();
    }
}


CommandPair builtins[] = {
    { "exit", &exitbi },
    { "cd", &cd }
};

bool isbuiltin(char *command) {
    int len = sizeof(builtins) / sizeof(CommandPair);
    for(int i = 0 ; i < len ; i++) {
        if(strcmp(builtins[i].command, command) == 0) {
            return true;
        }
    }
    return false;
}
CommandPair *funfromcommand(char *command) {
    int len = sizeof(builtins) / sizeof(CommandPair);
    for(int i = 0 ; i < len ; i++) {
        if(strcmp(builtins[i].command, command) == 0) {
            return &builtins[i];
        }
    }
    return NULL;
}
void execbuiltin(int argc, char **argv) {
    char *command = argv[0];
    CommandPair *pair = funfromcommand(command);
    if(pair == NULL) {
        return;
    }
    void (*fun)(int, char **) = (*pair).fun;
    fun(argc, argv);
}
