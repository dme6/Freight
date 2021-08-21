#include <console/logger.h>
#include <fileio/config.h>

int setPort(int argc, const char** argv, const char* configLoc) {

    if(argc < 3) {
        logFewArgs();
        return 0;
    }

    if(!writeConfigEntry(configLoc, "port", argv[2])) return 0;

    return 1;

}