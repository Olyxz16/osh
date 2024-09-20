#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "colors.h"


void cwd(char **buf) {
    *buf = get_current_dir_name();
}

void user(char **buf) {
    *buf = getenv("USER");
    if(buf == NULL) {
        strcpy(*buf, "");
    }
}

char *checkhomedir(char *cwd) {
    char *homedir = getenv("HOME");
    if(homedir == NULL) {
        return cwd;
    }
    if (strstr(cwd, homedir) == NULL) {
        return cwd;
    }
    int cwdlen = strlen(cwd);
    int homelen = strlen(homedir);
    int remlen = cwdlen - homelen + 1;
    char *rem = (char *)malloc(remlen * sizeof(char));
    for(int i = 0 ; i < remlen ; i++) {
        rem[i] = cwd[i+homelen];
    }
    char *res = (char *)malloc((remlen+1) * sizeof(char));
    sprintf(res, "~%s", rem);
    free(cwd);
    free(rem);
    return res;
}

void prompt() {
    char *cwdbuf;
    cwd(&cwdbuf);
    char *userbuf;
    user(&userbuf);
    cwdbuf = checkhomedir(cwdbuf);

    char *format = _GN "%s"_0":"_BL"%s> " _0;
    int len = snprintf(NULL, 0, format, userbuf, cwdbuf);
    char *prompt = malloc(len * sizeof(char));
    sprintf(prompt, format, userbuf, cwdbuf);
    fputs(prompt, stderr);
    
    free(cwdbuf);
    free(prompt);
}
