#include <string.h>
#include <path/make.h>
#include <util/trackedBuffer.h>
#include <console/logger.h>
#include "functions/config.h"
#include "functions/listen.h"

int handleArgs(int argc, const char** argv) {

    if(argc < 2) {
        logFewArgs();
        return 0;
    }

    int returnVal = 1;

    TrackedBuffer* configPath = makeConfigPath();

    if(strcmp(argv[1], "setport") == 0) {

        if(!setPort(argc, argv, configPath->alloc)) returnVal = 0;

    } else if(strcmp(argv[1], "getport") == 0) {

        if(!getPort(argv, configPath->alloc)) returnVal = 0;

    } else if(strcmp(argv[1], "listen") == 0) {
    
        if(!listenFunction(configPath->alloc)) returnVal = 0;

    } else {

        logError("Invalid arguments.");
        returnVal = 0;

    }

    cleanTrackedBuffer(configPath);
    return returnVal;

}