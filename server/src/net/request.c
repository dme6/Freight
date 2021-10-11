#include <winsock2.h>
#include <util/trackedBuffer.h>
#include <console/logger.h>
#include <stdio.h>
#include <string.h>

int handleSignUp(SOCKET* clientSockP) {

    int returnVal = 1;

    TrackedBuffer* buffer = createTrackedBuffer(sizeof(char) * 20);
    TrackedBuffer* fullBuffer = createTrackedBuffer(0);

    for(;;) {

        int read = recv(*clientSockP, buffer->alloc, buffer->size, 0);

        if(read > 0) {
            size_t previousSize = fullBuffer->size;
            expandTrackedBuffer(fullBuffer, read);
            memcpy(fullBuffer->alloc + previousSize, buffer->alloc, read);
        } else if(read == 0) {
            logInfo("Connection closed.");
            break;
        } else {
            logError("Failed to recieve data.");
            returnVal = 0;
            break;
        }

    }

    logInfo(fullBuffer->alloc);

    cleanTrackedBuffer(buffer);

    return returnVal;

}