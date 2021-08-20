#include <stdio.h>
#include <stdlib.h>
#include "../../fileio/fileio.h"
#include "../../logger/logger.h"
#include "../../util/trackedBuffer.h"

int setServer(int argc, const char** argv, TrackedBuffer* configLoc) {

    if(argc < 4) {
        logFewArgs();
        cleanTrackedBuffer(configLoc);
        return 0;
    }

    if(!writeConfigEntry(configLoc, "serverIP", argv[2])) {
        cleanTrackedBuffer(configLoc);
        return 0;
    }
    if(!writeConfigEntry(configLoc, "serverPort", argv[3])) {
        cleanTrackedBuffer(configLoc);
        return 0;
    }

    return 1;

}

int getServer(const char** argv, TrackedBuffer* configLoc) {

    char* ip;
    char* port;

    if(!getConfigEntry(configLoc, "serverIP", &ip)) {
        cleanTrackedBuffer(configLoc);
        return 0;
    }
    if(!getConfigEntry(configLoc, "serverPort", &port)) {
        cleanTrackedBuffer(configLoc);
        return 0;
    }

    printf("IP: %s\nPort: %s\n", ip, port);

    free(ip);
    free(port);

    return 1;

}