#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include "builtin.h"

#define RUNNING -1
#define TERMINATED 0
#define ERROR 1

void printerror(char *command) {
    char *format = "%s";
    int len = snprintf(NULL, 0, format, command, errno, command);
    char *errorstr = malloc((len+1) * sizeof(char));
    sprintf(errorstr, format, command, errno, command);
    perror(errorstr);
    free(errorstr);
}

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
        printerror(command);
        exit(0);
    }

    return RUNNING;
}
