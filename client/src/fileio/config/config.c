#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/trackedBuffer.h>
#include <console/logger.h>

#define CSIZE sizeof(char)

/*
    Configuration files are used to store key-value pairs for the program.
    Any entry can be any size, but they must end with a new line.
*/

static void fAppend(TrackedBuffer* configBuffer, const char* name, const char* data) {
    // The two extra chars are "=" and "\n".
    expandTrackedBuffer(configBuffer, strlen(name) + strlen(data) + (CSIZE * 2));
    sprintf(configBuffer->alloc + strlen(configBuffer->alloc), "%s=%s\n", name, data);
}

static void fToL() {
    logError("Failed to locate the specified entry.");
}

int writeConfigEntry(const char* loc, const char* name, const char* data) {

    TrackedBuffer* configBuffer = createTrackedBuffer(CSIZE);
    ((char*) configBuffer->alloc)[0] = '\0';
    TrackedBuffer* lineBuffer = createTrackedBuffer(CSIZE);
    ((char*) lineBuffer->alloc)[0] = '\0';

    char buffer[50];

    FILE* fp = fopen(loc, "r");

    if(!fp) {
        logWarning("Failed to access configuration file. One will be created.");
        fclose(fopen(loc, "w"));
        fp = fopen(loc, "r");
    }

    int found = 0;
    
    while(fgets(buffer, sizeof(buffer), fp)) {

        expandTrackedBuffer(lineBuffer, strlen(buffer));
        strcat(lineBuffer->alloc, buffer);

        if(buffer[strlen(buffer) - 1] == '\n') {

            char nameTok[lineBuffer->size];
            strcpy(nameTok, lineBuffer->alloc);
            strtok(nameTok, "=");

            if(strcmp(nameTok, name) == 0) {
                fAppend(configBuffer, name, data);
                found = 1;
            } else {
                expandTrackedBuffer(configBuffer, strlen(lineBuffer->alloc));
                strcat(configBuffer->alloc, lineBuffer->alloc);
            }

            resizeTrackedBuffer(lineBuffer, CSIZE);
            clearTrackedBuffer(lineBuffer);

        }

    }

    if(!found) {
        fAppend(configBuffer, name, data);
    }

    fclose(fp);

    fp = fopen(loc, "w");
    fprintf(fp, configBuffer->alloc);

    fclose(fp);

    cleanTrackedBuffer(lineBuffer);
    cleanTrackedBuffer(configBuffer);

    return 1;

}


int getConfigEntry(const char* loc, const char* name, char** out) {

    TrackedBuffer* lineBuffer = createTrackedBuffer(CSIZE);
    ((char*) lineBuffer->alloc)[0] = '\0';

    char buffer[50];

    FILE* fp = fopen(loc, "r");

    if(!fp) {

        fToL();
        fclose(fp);
        cleanTrackedBuffer(lineBuffer);

        return 0;

    }

    int returnVal = 0;

    while(fgets(buffer, sizeof(buffer), fp)) {

        expandTrackedBuffer(lineBuffer, strlen(buffer));
        strcat(lineBuffer->alloc, buffer);

        if(buffer[strlen(buffer) - 1] == '\n') {
            
            char nameTok[lineBuffer->size];
            strcpy(nameTok, lineBuffer->alloc);
            strtok(nameTok, "=");

            if(strcmp(nameTok, name) == 0) {

                char* dataTok = strtok(0, "=");
                dataTok[strlen(dataTok) - 1] = '\0';

                // TODO: Change later if there is a better solution.
                char* dataTokAlloc = malloc(strlen(dataTok) + 1);
                strcpy(dataTokAlloc, dataTok);
                *out = dataTokAlloc;

                returnVal = 1;
                break;

            }

            resizeTrackedBuffer(lineBuffer, CSIZE);
            clearTrackedBuffer(lineBuffer);

        }

    }

    if(returnVal == 0) fToL();

    fclose(fp);
    cleanTrackedBuffer(lineBuffer);

    return returnVal;

}