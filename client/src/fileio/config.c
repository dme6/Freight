#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../logger/logger.h"
#include "../util/trackedBuffer.h"

/*
    Configuration files are used to store key value pairs for the program.
    Any entry can be any size, but they must end with a new line.
*/

static void fAppend(TrackedBuffer* configBuffer, const char* name, const char* data) {
    expandTrackedBuffer(configBuffer, strlen(name) + strlen(data) + 2);
    sprintf(configBuffer->alloc + strlen(configBuffer->alloc), "%s=%s\n", name, data);
}

static void fToL() {
    logError("Failed to locate the specified entry.");
}

int writeConfigEntry(const char* loc, const char* name, const char* data) {

    TrackedBuffer* configBuffer = createTrackedBuffer(sizeof(char));
    ((char*) configBuffer->alloc)[0] = '\0';
    TrackedBuffer* lineBuffer = createTrackedBuffer(sizeof(char));
    ((char*) lineBuffer->alloc)[0] = '\0';

    char buffer[10];

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

            resizeTrackedBuffer(lineBuffer, sizeof(char));
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


int getConfigEntry(char** out, const char* loc, const char* name) {

    TrackedBuffer* lineBuffer = createTrackedBuffer(sizeof(char));
    ((char*) lineBuffer->alloc)[0] = '\0';

    char buffer[10];

    FILE* fp = fopen(loc, "r");

    if(!fp) {

        fToL();
        fclose(fp);
        cleanTrackedBuffer(lineBuffer);

        return 0;

    }

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

                // I'm not sure if this is a good idea.
                char* dataTokAlloc = malloc(strlen(dataTok) + 1);
                strcpy(dataTokAlloc, dataTok);
                *out = dataTokAlloc;

                fclose(fp);
                cleanTrackedBuffer(lineBuffer);

                return 1;

            }

            resizeTrackedBuffer(lineBuffer, sizeof(char));
            clearTrackedBuffer(lineBuffer);

        }

    }

    fToL();
    fclose(fp);
    cleanTrackedBuffer(lineBuffer);

    return 0;

}