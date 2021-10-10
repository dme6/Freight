#include <stdio.h>
#include <winsock2.h>
#include <console/logger.h>
#include <fileio/config.h>
#include <util/trackedBuffer.h>
#include <net/init.h>
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
    if(!getConfigEntry(configLoc, "serverPort", &port)) return 0;

    SOCKET sock;
    if(!startConnection(ip, (u_short) strtoul(port, 0, 0), &sock)) {
        returnVal = 0;
        goto cleanup1;
    }

    size_t dataSize = strlen(argv[2]) + 1 + (strlen(argv[3]) + 1);

    TrackedBuffer* header = createTrackedBuffer(sizeof(int) * 2);
    ((int*) header->alloc)[0] = 1;
    ((int*) header->alloc)[1] = dataSize;
    sendData(&sock, header);

    TrackedBuffer* data = createTrackedBuffer(dataSize);
    sprintf(data->alloc, "%s;%s", argv[2], argv[3]);
    sendData(&sock, data);

    shutdown(sock, SD_SEND);
    cleanNet(&sock);
    cleanTrackedBuffer(header);
    cleanTrackedBuffer(data);
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