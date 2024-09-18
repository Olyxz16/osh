#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


typedef struct command_pair {
    char *command;
    int (*fun)(int, char **);
} CommandPair;


int exitbi() {
    exit(0);
}

int cd(int argc, char **args) {
    if(argc < 2) {
        return 1;
    }
    const char *path = args[1];
    chdir(path);
    return -1;
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
int execbuiltin(int argc, char **argv) {
    char *command = argv[0];
    CommandPair *pair = funfromcommand(command);
    if(pair == NULL) {
        return -1;
    }
    int (*fun)(int, char **) = (*pair).fun;
    int status = fun(argc, argv);
    return status;
}
