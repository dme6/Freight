#pragma once

#include <winsock2.h>
#include <util/trackedBuffer.h>

int sendData(SOCKET* sock, TrackedBuffer* data);
int recieveData(SOCKET* sock);