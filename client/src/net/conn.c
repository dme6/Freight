#include <winsock2.h>
#include <console/logger.h>
#include <net/init.h>

int startConnection(const char* ip, u_short port, SOCKET* sock) {

    if(!initNet(sock)) return 0;

    struct sockaddr_in addr = {
        .sin_addr.s_addr = inet_addr(ip),
        .sin_family = AF_INET,
        .sin_port = htons(port)
    };
    
    if(connect(*sock, (struct sockaddr*) &addr, sizeof(addr)) < 0) {

        logError("Failed to connect.");
        cleanNet(sock);
        return 0;

    }

    logInfo("Connected.");

    return 1;

}