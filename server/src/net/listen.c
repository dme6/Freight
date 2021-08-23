#include <winsock2.h>
#include <net/init.h>
#include <console/logger.h>

int startListening(u_short port) {

    SOCKET sock;
    if(!initNet(&sock)) return 0;

    struct sockaddr_in addr = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(port)
    };

    if(bind(sock, (struct sockaddr*) &addr, sizeof(addr)) == SOCKET_ERROR) {
        
        logError("Failed to bind.");
        return 0;
        
    }

    listen(sock, 3);

    while(1) {

        struct sockaddr_in clientAddr;
        int clientAddrLen = sizeof(struct sockaddr_in);

        SOCKET clientSock;

        if((clientSock = accept(sock, (struct sockaddr*) &clientAddr, &clientAddrLen)) == INVALID_SOCKET) {

            logError("Failed to accept connection.");
            return 0;

        }

        logInfo("Connected.");

        closesocket(clientSock);
        break;

    }

    closesocket(sock);
    WSACleanup();

    return 1;

}