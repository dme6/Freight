#pragma once

#include <winsock2.h>

int initNet(SOCKET* sock);
void cleanNet(SOCKET* sock);