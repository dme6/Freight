#include <string.h>
#include "../logger/logger.h"
#include "./functions/functions.h"

static const char* configLoc = "./config.dat";

int handleArgs(int argc, const char* const* argv) {

    if(argc < 2) {
        logFewArgs();
        return 0;
    }

    if(strcmp(argv[1], "setserver") == 0) {

        if(!setServer(argc, argv, configLoc)) return 0;

    } else if(strcmp(argv[1], "getserver") == 0) {

        if(!getServer(argv, configLoc)) return 0;

    } else if(strcmp(argv[1], "signup") == 0) {

        if(!signUp(argc, argv, configLoc)) return 0;

    }

    return 1;

}