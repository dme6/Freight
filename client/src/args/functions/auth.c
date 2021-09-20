#include <stdio.h>
#include <winsock2.h>
#include <console/logger.h>
#include <fileio/config.h>
#include <util/trackedBuffer.h>
#include "../../net/conn.h"
#include "../../net/data.h"

int signUp(int argc, const char** argv, const char* configLoc) {

    if(argc < 4) {
        logFewArgs();
        return 0;
    }

    char* ip;
    char* port;

    if(!getConfigEntry(configLoc, "serverIP", &ip)) return 0;
    if(!getConfigEntry(configLoc, "serverPort", &port)) return 0;

    SOCKET sock;
    if(!startConnection(ip, (u_short) strtoul(port, 0, 0), &sock)) return 0;

    TrackedBuffer* buffer = createTrackedBuffer(sizeof(char) * 9);
    strcpy(buffer->alloc, "Testing.");

    sendData(&sock, buffer);
    sendData(&sock, buffer);

    shutdown(sock, SD_SEND);
    endConnection(&sock);

    cleanTrackedBuffer(buffer);
    free(ip);
    free(port);

    return 1;

}

int logIn(int argc, const char** argv, const char* configLoc) {

    if(argc < 4) {
        logFewArgs();
        return 0;
    }

    return 1;

}