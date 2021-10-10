#include <winsock2.h>
#include <util/trackedBuffer.h>
#include <stdint.h>
#include <console/logger.h>
#include <stdio.h>

int handleSignUp(SOCKET* clientSockP, int size) {

    int returnVal = 1;

    TrackedBuffer* buffer = createTrackedBuffer(size);

    for(;;) {

        int read = recv(*clientSockP, buffer->alloc, buffer->size, 0);

        if(read > 0) {
            logInfo(buffer->alloc);
        } else if(read == 0) {
            logInfo("Connection closed.");
            break;
        } else {
            logError("Failed to recieve data.");
            returnVal = 0;
            break;
        }

    }

    cleanTrackedBuffer(buffer);

    return returnVal;

}