#include <winsock2.h>
#include <console/logger.h>

int startConnection(const char* ip, u_short port, SOCKET* outSock) {

    WSADATA wsa;
    if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {

        logError("Failed to initialize the Windows Sockets API.");
        return 0;

    }

    SOCKET sock;
    if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {

        logError("Failed to create a socket.");
        return 0;
        
    }

    struct sockaddr_in addr = {
        .sin_addr.s_addr = inet_addr(ip),
        .sin_family = AF_INET,
        .sin_port = htons(port)
    };
    
    if(connect(sock, (struct sockaddr*) &addr, sizeof(addr)) < 0) {

        logError("Failed to connect.");
        return 0;

    }

    return 1;

}

void endConnection(SOCKET* s) {

    closesocket(*s);
    WSACleanup();

}