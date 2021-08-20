#include "../../fileio/fileio.h"
#include "../../logger/logger.h"
#include "../../util/trackedBuffer.h"

int signUp(int argc, const char** argv, TrackedBuffer* configLoc) {

    if(argc < 4) {
        logFewArgs();
        cleanTrackedBuffer(configLoc);
        return 0;
    }

    cleanTrackedBuffer(configLoc);
    // writeConfigEntry(configLoc, "password", argv[3]);

    return 1;

}

int logIn(int argc, const char** argv, TrackedBuffer* configLoc) {

    if(argc < 4) {
        logFewArgs();
        cleanTrackedBuffer(configLoc);
        return 0;
    }

    cleanTrackedBuffer(configLoc);

    return 1;

}