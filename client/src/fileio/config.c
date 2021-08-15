#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../logger/logger.h"

static void fAppend(char* configBuffer, const char* name, const char* data) {
    sprintf(configBuffer + strlen(configBuffer), "%s=%s\n", name, data);
}

static void fToL() {
    logError("Failed to locate the specified entry.");
}

int writeConfigEntry(const char* loc, const char* name, const char* data) {

    char* configBuffer = malloc(sizeof(char) * 1000);
    char lineBuffer[50];

    configBuffer[0] = '\0';

    FILE* fp = fopen(loc, "r");

    if(!fp) {
        logWarning("Config file doesn't exist. One will be created.");
        fclose(fp);
        fclose(fopen(loc, "w"));
        fp = fopen(loc, "r");
    }

    int found = 0;
    
    while(fgets(lineBuffer, sizeof(lineBuffer), fp)) {

        char nameTok[sizeof(lineBuffer)];
        strcpy(nameTok, lineBuffer);
        strtok(nameTok, "=");

        if(strcmp(nameTok, name) == 0) {
            fAppend(configBuffer, name, data);
            found = 1;
        } else {
            strcat(configBuffer, lineBuffer);
        }

    }

    if(!found) {
        fAppend(configBuffer, name, data);
    }

    fclose(fp);

    fp = fopen(loc, "w");
    fprintf(fp, configBuffer);

    fclose(fp);
    free(configBuffer);

    return 1;

}

int getConfigEntry(char* out, const char* loc, const char* name) {

    char lineBuffer[50];

    FILE* fp = fopen(loc, "r");

    if(!fp) {
        fToL();
        return 0;
    }

    int found = 0;

    while(fgets(lineBuffer, sizeof(lineBuffer), fp)) {

        char tok[sizeof(lineBuffer)];
        strcpy(tok, lineBuffer);
        strtok(tok, "=");

        if(strcmp(tok, name) == 0) {

            char* data = strtok(0, "=");
            data[strlen(data) - 1] = '\0';
            strcpy(out, data);

            found = 1;
            fclose(fp);
            return 1;

        }

    }

    if(!found) {
        fclose(fp);
        fToL();
        return 0;
    }

    return 1;

}