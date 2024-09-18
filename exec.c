#include <string.h>
#include <stdbool.h>
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
    // not builtin
    return RUNNING;
}
