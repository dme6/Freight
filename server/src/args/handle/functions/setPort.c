#include <console/logger.h>

int setPort(int argc, const char** argv, const char* configLoc) {

    if(argc < 3) {
        logFewArgs();
        return 0;
    }

    return 1;

}