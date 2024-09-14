#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int cwd(char **buf) {
    *buf = get_current_dir_name();
    int len = strlen(*buf);
    return len;
}

int user(char **buf) {
    *buf = getlogin();
    int len = strlen(*buf);
    return len;
}

void prompt() {
    char *cwdbuf;
    int cwdlen = cwd(&cwdbuf);
    char *userbuf;
    int userlen = user(&userbuf);
    char *prompt = malloc((cwdlen + userlen + 10) * sizeof(char));
    sprintf(prompt, "%s:%s> ", userbuf, cwdbuf);
    fputs(prompt, stderr);
    
    free(cwdbuf);
    free(prompt);
}
