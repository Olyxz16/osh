#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include "builtin.h"

#define RUNNING -1
#define TERMINATED 0
#define ERROR 1


int exec(int argc, char **argv) {
    if(argc == 0) {
        return RUNNING;
    }
    if(isbuiltin(argv[0])) {
        int status = execbuiltin(argc, argv);
        return status;
    }
    
    char *command = argv[0];
    __pid_t child_pid = fork();
    if(child_pid) { // we are parent
        wait(NULL);
    } else { // we are child
        execvp(command, argv);
        exit(0);
    }

    return RUNNING;
}
