#ifndef PARSER_H
#define PARSER_H

typedef struct command_struct {
    char *command;
    int argc;
    char **args;
    int in;
    int out;
}  command_t;

int parse(char *line, command_t ***commands);

#endif
