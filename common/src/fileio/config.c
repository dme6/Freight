#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/trackedBuffer.h>
#include <console/logger.h>

/*
    Configuration files are used to store key-value pairs for the program.
    Any entry can be any size, but they must end with a new line.
*/

static void fAppend(TrackedBuffer* configBuffer, const char* name, const char* data) {
    // The two extra chars are "=" and "\n".
    expandTrackedBuffer(configBuffer, strlen(name) + strlen(data) + (sizeof(char) * 2));
    sprintf(configBuffer->alloc + strlen(configBuffer->alloc), "%s=%s\n", name, data);
}

int writeConfigEntry(const char* loc, const char* name, const char* data) {

    TrackedBuffer* configBuffer = createTrackedBuffer(sizeof(char));
    ((char*) configBuffer->alloc)[0] = '\0';
    TrackedBuffer* lineBuffer = createTrackedBuffer(sizeof(char));
    ((char*) lineBuffer->alloc)[0] = '\0';

    char buffer[20];

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

int getConfigEntry(const char* loc, const char* name, char** out) {

    TrackedBuffer* lineBuffer = createTrackedBuffer(sizeof(char));
    ((char*) lineBuffer->alloc)[0] = '\0';

    char buffer[20];

    FILE* fp = fopen(loc, "r");

    if(!fp) {
        cleanTrackedBuffer(lineBuffer);
        return 0;
    }

    int found = 0;
    
    while(fgets(buffer, sizeof(buffer), fp)) {

        expandTrackedBuffer(lineBuffer, strlen(buffer));
        strcat(lineBuffer->alloc, buffer);

        if(buffer[strlen(buffer) - 1] == '\n') {
            
            char lineCopy[lineBuffer->size];
            strcpy(lineCopy, lineBuffer->alloc);
            char* nameTok = strtok(lineCopy, "=");

            if(strcmp(nameTok, name) == 0) {

                char* dataTok = strtok(0, "");
                // Remove new line at end.
                dataTok[strlen(dataTok) - 1] = '\0';

                char* dataTokAlloc = malloc(strlen(dataTok) + 1);
                strcpy(dataTokAlloc, dataTok);
                *out = dataTokAlloc;

                found = 1;
                break;

            }

            resizeTrackedBuffer(lineBuffer, sizeof(char));
            clearTrackedBuffer(lineBuffer);

        }

    }

    if(!found) logError("Failed to locate the specified entry.");
    fclose(fp);
    cleanTrackedBuffer(lineBuffer);

    return found;

}