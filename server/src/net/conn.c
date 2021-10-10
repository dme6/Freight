#include <winsock2.h>
#include <windows.h>
#include <util/trackedBuffer.h>
#include <console/logger.h>
#include <stdio.h>
#include <stdint.h>
#include "request.h"

DWORD WINAPI handleFunc(void* clientSockP) {

    int returnVal = 1;

    TrackedBuffer* headerBuffer = createTrackedBuffer(sizeof(int) * 2);
    SOCKET clientSock = *((SOCKET*) clientSockP);

    if(recv(clientSock, headerBuffer->alloc, headerBuffer->size, 0) == SOCKET_ERROR) {
        // ...
    }

    int* header = headerBuffer->alloc;

    switch(header[0]) {
        case 1: {
            if(!handleSignUp(clientSockP, header[1])) returnVal = 0;
            break;
        }
    }

    cleanTrackedBuffer(headerBuffer);
    shutdown(clientSock, SD_SEND);
    closesocket(clientSock);

    return returnVal;

}

void handleConnection(SOCKET* clientSock) {

    HANDLE thread = CreateThread(0, 0, handleFunc, clientSock, 0, 0);
    // Detatch.
    CloseHandle(thread);

}