#include <fileio/config.h>
#include "../../net/listen.h"

int listenFunction(const char* configLoc) {

    int returnVal = 1;

    char* port;

    if(!getConfigEntry(configLoc, "port", &port)) return 0;

    if(!startListening((u_short) strtoul(port, 0, 0))) returnVal = 0;

    free(port);
    
    return returnVal;

}