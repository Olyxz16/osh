#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include "parser.h"


/*================================================*/
/*                    TYPE                        */
/*================================================*/


command_t *def(char *comname) {
    command_t *command = malloc(sizeof(command_t));
    command->command = comname;
    command->argc = 1;
    command->args = malloc(sizeof(char *));
    command->args[0] = comname;
    command->in = -1;
    command->out = -1;
    return command;
}



/*================================================*/
/*                    LINE                        */
/*================================================*/


int countargs(char *line) {
    int c = 0;
    int len = strlen(line);
    bool previsspace = true;
    for(int i = 0 ; i < len ; i++) {
        bool isspace = line[i] == ' ';
        if(!isspace && previsspace) {
            c++;   
        }
        previsspace = isspace;
    }
    return c;
}

char *substring(char *str, int start, int end) {
    int len = end - start + 2;
    char *res = (char *)malloc(len * sizeof(char));
    for(int i = 0 ; i < len ; i++) {
        res[i] = str[i + start];
    }
    res[len-1] = '\0';
    return res;
}

char **split(char *line, int count) {
    char **args = malloc((count+1) * sizeof(char *));
    int len = strlen(line);
    int curr = 0;
    int start = 0;
    bool previsspace = true;
    for(int i = 0 ; i < len ; i++) {
        bool isspace = line[i] == ' ';
        if(!isspace && previsspace) {
            start = i;
        }
        if(isspace && !previsspace) {
            int end = i-1;
            args[curr] = substring(line, start, end);
            curr++;
        }
        previsspace = isspace;
    }
    if(!previsspace) {
        int end = len-1;
        args[curr] = substring(line, start, end);
    }
    return args;
}

/*================================================*/
/*                   TOKENS                       */
/*================================================*/

void addcommand(int *comc, command_t ***commands, command_t *command) {
    (*comc)++;
    *commands = realloc(*commands, *comc * sizeof(command_t));
    (*commands)[(*comc)-1] = command;
}

void addarg(command_t *command, char *arg) {
    command->argc += 1;
    command->args = realloc(command->args, command->argc * sizeof(char *));
    (command->args)[command->argc-1] = arg;
}

void parsetoken(int *ind, char **tokens, int *comc, command_t ***commands) {
    char *curr = tokens[*ind];
    char *next = tokens[(*ind)+1];
    if(strcmp(curr, "&&") == 0) {
        if(next == NULL) {
             return;
        }
        command_t *cmd = def(next);
        addcommand(comc, commands, cmd);
        //skip next;
        (*ind)++;
        return;
    }
    if(strcmp(curr, "|") == 0) {
        if(next == NULL) {
            return;
        }
        command_t *currcom = (*commands)[(*comc)-1];
        command_t *nextcom = def(next);
        int fp[2];
        pipe(fp);
        currcom->out = fp[1];
        nextcom->in = fp[0];
        addcommand(comc, commands, nextcom);
        //skip next;
        (*ind)++;
        return;
    }
    //First command
    if(*comc == 0) {
        command_t *cmd = def(curr);
        addcommand(comc, commands, cmd);
        return;
    }
    addarg((*commands)[(*comc)-1], curr);
    return;
}

int parsetokens(int argc, char **tokens, command_t ***commands) {
    int comc = 0;
    int step = 0;
    while(step < argc) {
        parsetoken(&step, tokens, &comc, commands); 
        step++;
    }
    return comc;
}

int parse(char *line, command_t ***commands) {
    int argc = countargs(line);
    char **tokens = split(line, argc);
    *commands = malloc(sizeof(command_t *));
    int commandc = parsetokens(argc, tokens, commands);
    return commandc;
}
