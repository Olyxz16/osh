#include <string.h>

#define RUNNING -1
#define TERMINATED 0
#define ERROR 1


int exec(int argc, char **argv) {
    if(argc == 0) {
        return RUNNING;        
    }
    if(argc == 1 && strcmp(argv[0], "exit") == 0) {
        return TERMINATED;
    }

    return RUNNING;
}
