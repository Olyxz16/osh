#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include "builtin.h"
#include "colors.h"
#include "parser.h"

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

void execcmd(command_t *cmd) {
    if(isbuiltin(cmd->command)) {
        execbuiltin(cmd->argc, cmd->args);
        return;
    }
    
    __pid_t child_pid = fork();
    if(child_pid) { // we are parent
        close(cmd->out);
    } else { // we are child
        if(cmd->in != -1) {
            dup2(cmd->in, STDIN_FILENO);
        }
        if(cmd->out != -1) {
            dup2(cmd->out, STDOUT_FILENO);
        }
        close(cmd->in);
        execvp(cmd->command, cmd->args);
        printerror(cmd->command);
        exit(0);
    }
}

void exec(int comc, command_t **commands) {
    for(int i = 0 ; i < comc ; i++) {
        execcmd(commands[i]);
    } 
}
