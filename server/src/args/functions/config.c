#include <stdio.h>
#include <stdlib.h>
#include <fileio/config.h>
#include <console/logger.h>

int getPort(const char** argv, const char* configLoc) {

    char* port;

    if(!getConfigEntry(configLoc, "port", &port)) return 0;

    printf("Port: %s\n", port);

    free(port);
    return 1;

}

int setPort(int argc, const char** argv, const char* configLoc) {

    if(argc < 3) {
        logFewArgs();
        return 0;
    }

    if(!writeConfigEntry(configLoc, "port", argv[2])) return 0;

    return 1;

}