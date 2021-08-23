#include <stdio.h>
#include <winsock2.h>
#include <console/logger.h>
#include <fileio/config.h>
#include "../../net/conn.h"

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
    endConnection(&sock);

    return 1;

}

int logIn(int argc, const char** argv, const char* configLoc) {

    if(argc < 4) {
        logFewArgs();
        return 0;
    }

    return 1;

}