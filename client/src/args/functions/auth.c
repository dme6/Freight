#include "../../fileio/fileio.h"
#include "../../logger/logger.h"

int signUp(int argc, const char** argv, const char* configLoc) {

    if(argc < 4) {
        logFewArgs();
        return 0;
    }

    return 1;

}

int logIn(int argc, const char** argv, const char* configLoc) {

    if(argc < 4) {
        logFewArgs();
        return 0;
    }

    return 1;

}