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

char *checkhomedir(int cwdlen, char *cwd) {
    char *homedir = getenv("HOME");
    if(homedir == NULL) {
        return cwd;
    }
    if (strstr(cwd, homedir) == NULL) {
        return cwd;
    }
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
    int cwdlen = cwd(&cwdbuf);
    char *userbuf;
    int userlen = user(&userbuf);
    cwdbuf = checkhomedir(cwdlen, cwdbuf);
    char *prompt = malloc((cwdlen + userlen + 10) * sizeof(char));
    sprintf(prompt, "%s:%s> ", userbuf, cwdbuf);
    fputs(prompt, stderr);
    
    free(cwdbuf);
    free(prompt);
}
