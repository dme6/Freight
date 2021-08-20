#include <string.h>
#include <windows.h>
#include <stdio.h>
#include "../logger/logger.h"
#include "./functions/functions.h"
#include "../util/trackedBuffer.h"

#define CONFIG_NAME "config.dat"

static TrackedBuffer* makeConfigPath() {

    TrackedBuffer* pathBuffer = createTrackedBuffer(sizeof(char) * 10);

    while(1) {

        GetModuleFileName(0, pathBuffer->alloc, pathBuffer->size);
        if(GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
            expandTrackedBuffer(pathBuffer, sizeof(char) * 10);
        } else {
            break;
        }

    }
    
    size_t expansion = strlen(CONFIG_NAME) - (pathBuffer->size - strlen(pathBuffer->alloc));

    if(expansion > 0) expandTrackedBuffer(pathBuffer, expansion);
    strrchr(pathBuffer->alloc, '\\')[1] = '\0';
    strcat(pathBuffer->alloc, CONFIG_NAME);

    return pathBuffer;

}

int handleArgs(int argc, const char** argv) {

    if(argc < 2) {
        logFewArgs();
        return 0;
    }

    TrackedBuffer* configPath = makeConfigPath();

    if(strcmp(argv[1], "setserver") == 0) {

        if(!setServer(argc, argv, configPath)) return 0;

    } else if(strcmp(argv[1], "getserver") == 0) {

        if(!getServer(argv, configPath)) return 0;

    } else if(strcmp(argv[1], "signup") == 0) {

        if(!signUp(argc, argv, configPath)) return 0;

    } else if(strcmp(argv[1], "login") == 0) {

        if(!logIn(argc, argv, configPath)) return 0;

    } else {

        logError("Invalid arguments.");
        return 0;

    }

    return 1;

}