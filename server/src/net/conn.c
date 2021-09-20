#include <winsock2.h>
#include <windows.h>
#include <util/trackedBuffer.h>
#include <console/logger.h>
#include <stdio.h>

DWORD WINAPI handleFunc(void* clientSockP) {

    TrackedBuffer* buffer = createTrackedBuffer(sizeof(char) * 1024);
    SOCKET clientSock = *((SOCKET*) clientSockP);

    while(1) {

        int read;

        if((read = recv(clientSock, buffer->alloc, buffer->size, 0)) == SOCKET_ERROR) {

            logError("Failed to recieve data.");
            return 1;

	    }

        if(read > 0) {
            logInfo(buffer->alloc);
        } else break;

    }

    shutdown(clientSock, SD_SEND);
    closesocket(clientSock);

    cleanTrackedBuffer(buffer);

    return 0;

}

void handleConnection(SOCKET* clientSock) {

    CreateThread(0, 0, handleFunc, clientSock, 0, 0);

}