#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

char **split(char *line) {
    int argc = countargs(line);
    char **args = malloc(argc * sizeof(char *));
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

int parseline(char *line, char ***args) {
    int argc = countargs(line);
    *args = split(line);
    return argc;
}
