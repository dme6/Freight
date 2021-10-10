#include <string.h>
#include <path/make.h>
#include <util/trackedBuffer.h>
#include <console/logger.h>
#include "functions/config.h"
#include "functions/auth.h"

int handleArgs(int argc, const char** argv) {

    if(argc < 2) {
        logFewArgs();
        return 0;
    }

    int returnVal = 1;

    TrackedBuffer* configPath = makeConfigPath();

    if(strcmp(argv[1], "setserver") == 0) {

        if(!setServer(argc, argv, configPath->alloc)) returnVal = 0;

    } else if(strcmp(argv[1], "getserver") == 0) {

        if(!getServer(configPath->alloc)) returnVal = 0;

    } else if(strcmp(argv[1], "signup") == 0) {

        if(!signUp(argc, argv, configPath->alloc)) returnVal = 0;

    } else if(strcmp(argv[1], "login") == 0) {

        if(!logIn(argc, argv, configPath->alloc)) returnVal = 0;

    } else {

        logError("Invalid arguments.");
        returnVal = 0;

    }

    cleanTrackedBuffer(configPath);
    return returnVal;

}