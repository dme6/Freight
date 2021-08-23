#include <winsock2.h>
#include <util/trackedBuffer.h>
#include <console/logger.h>

int sendData(SOCKET* sock, TrackedBuffer* tb) {

    if(send(*sock, tb->alloc, tb->size, 0) < 0) {

        logError("Failed to send data.");
        return 0;
        
    }

    return 1;

}

int recieveData(SOCKET* sock) {

    int read;
    TrackedBuffer* buffer = createTrackedBuffer(sizeof(char) * 1024);

    do {

        if((read = recv(*sock, buffer->alloc, buffer->size, 0)) == SOCKET_ERROR) {

            logError("Failed to recieve data.");
            return 0;
            
        }

        logInfo("Chunk recieved.");

    } while(read > 0);

    return 1;
    
}