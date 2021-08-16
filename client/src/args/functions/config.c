#include <stdio.h>
#include "../../fileio/fileio.h"
#include "../../logger/logger.h"

int setServer(int argc, const char* const* argv, const char* configLoc) {

    if(argc < 4) {
        logFewArgs();
        return 0;
    }

    if(!writeConfigEntry(configLoc, "serverIP", argv[2])) return 0;
    if(!writeConfigEntry(configLoc, "serverPort", argv[3])) return 0;

    return 1;

}

int getServer(const char* const* argv, const char* configLoc) {

    char ip[50];
    char port[50];
    char final[114];

    if(!getConfigEntry(ip, configLoc, "serverIP")) return 0;
    if(!getConfigEntry(port, configLoc, "serverPort")) return 0;

    sprintf(final, "\n\nIP: %s\nPort: %s", ip, port);

    logInfo(final);

    return 1;

}