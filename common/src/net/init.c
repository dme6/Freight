#include <winsock2.h>
#include <console/logger.h>

int initNet(SOCKET* sock) {

    WSADATA wsd;
    if(WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {

        logError("Failed to initialize the Windows Sockets API.");
        return 0;

    }

    if((*sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {

        logError("Failed to create a socket.");
        WSACleanup();
        return 0;
        
    }

    return 1;

}

void cleanNet(SOCKET* sock) {

    closesocket(*sock);
    WSACleanup();

}