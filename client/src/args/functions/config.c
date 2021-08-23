#include <stdio.h>
#include <stdlib.h>
#include <console/logger.h>
#include <fileio/config.h>

int setServer(int argc, const char** argv, const char* configLoc) {

    if(argc < 4) {
        logFewArgs();
        return 0;
    }

    if(!writeConfigEntry(configLoc, "serverIP", argv[2])) return 0;
    if(!writeConfigEntry(configLoc, "serverPort", argv[3])) return 0;

    return 1;

}

int getServer(const char* configLoc) {

    char* ip;
    char* port;

    if(!getConfigEntry(configLoc, "serverIP", &ip)) return 0;
    if(!getConfigEntry(configLoc, "serverPort", &port)) return 0;

    printf("IP: %s\nPort: %s\n", ip, port);

    free(ip);
    free(port);

    return 1;

}