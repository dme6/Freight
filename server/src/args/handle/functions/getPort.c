#include <stdio.h>
#include <fileio/config.h>

int getPort(const char** argv, const char* configLoc) {

    char* port;

    if(!getConfigEntry(configLoc, "port", &port)) return 0;

    printf("Port: %s\n", port);

    free(port);

    return 1;

}