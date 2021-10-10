#pragma once

#include <winsock2.h>

int startConnection(const char* ip, u_short port, SOCKET* outSock);
