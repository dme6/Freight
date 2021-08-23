#include <fileio/config.h>
#include "../../net/listen.h"

int listenFunction(const char* configLoc) {

    char* port;

    if(!getConfigEntry(configLoc, "port", &port)) return 0;

    if(!startListening((u_short) strtoul(port, 0, 0))) return 0;

    return 1;

}