#include <stdio.h>
#include <winsock2.h>
#include <console/logger.h>
#include <fileio/config.h>
#include <util/trackedBuffer.h>
#include <net/init.h>
#include <stdint.h>
#include "../../net/conn.h"
#include "../../net/data.h"

int signUp(int argc, const char** argv, const char* configLoc) {

    int returnVal = 1;

    if(argc < 4) {
        logFewArgs();
        return 0;
    }

    char* ip;
    char* port;

    if(!getConfigEntry(configLoc, "serverIP", &ip)) return 0;
    if(!getConfigEntry(configLoc, "serverPort", &port)) {
        returnVal = 0;
        goto cleanup1;
    }

    SOCKET sock;
    if(!startConnection(ip, (u_short) strtoul(port, 0, 0), &sock)) {
        returnVal = 0;
        goto cleanup2;
    }

    size_t dataSize = strlen(argv[2]) + 1 + (strlen(argv[3]) + 1);

    TrackedBuffer* header = createTrackedBuffer(sizeof(uint8_t));
    ((uint8_t*) header->alloc)[0] = 0x01;
    if(!sendData(&sock, header)) {
        returnVal = 0;
        goto cleanup3;
    }

    TrackedBuffer* data = createTrackedBuffer(dataSize);
    sprintf(data->alloc, "%s;%s", argv[2], argv[3]);
    if(!sendData(&sock, data)) returnVal = 0;

    cleanTrackedBuffer(data);
cleanup3:
    shutdown(sock, SD_SEND);
    cleanNet(&sock);
    cleanTrackedBuffer(header);
cleanup2:
    free(port);
cleanup1:
    free(ip);

    return returnVal;

}

int logIn(int argc, const char** argv, const char* configLoc) {

    if(argc < 4) {
        logFewArgs();
        return 0;
    }

    return 1;

}