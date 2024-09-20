#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include "builtin.h"
#include "colors.h"

void printerror(char *command) {
    char *format = "%s";
    int len = snprintf(NULL, 0, format, command, errno, command);
    char *errorstr = malloc((len+1) * sizeof(char));
    sprintf(errorstr, format, command, errno, command);
    
    fontred(); 
    perror(errorstr);
    fontreset();
    
    free(errorstr);
}

void exec(int argc, char **argv) {
    if(argc == 0) {
        return;
    }
    if(isbuiltin(argv[0])) {
        execbuiltin(argc, argv);
        return;
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
}
