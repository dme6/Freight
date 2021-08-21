#include <windows.h>
#include <string.h>
#include <util/trackedBuffer.h>

#define CONFIG_NAME "config.dat"
#define CSIZE sizeof(char)

TrackedBuffer* makeConfigPath() {

    TrackedBuffer* pathBuffer = createTrackedBuffer(CSIZE * 10);

    while(1) {

        GetModuleFileName(0, pathBuffer->alloc, pathBuffer->size);
        if(GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
            expandTrackedBuffer(pathBuffer, CSIZE * 10);
        } else {
            break;
        }

    }
    
    // How much to expand buffer before adding CONFIG_NAME.
    size_t expansion = (strlen(CONFIG_NAME) + 1) - (pathBuffer->size - strlen(pathBuffer->alloc));

    if(expansion > 0) expandTrackedBuffer(pathBuffer, expansion);
    strrchr(pathBuffer->alloc, '\\')[1] = '\0';
    strcat(pathBuffer->alloc, CONFIG_NAME);

    return pathBuffer;

}