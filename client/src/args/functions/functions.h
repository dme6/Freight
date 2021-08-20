#pragma once

#include "../../util/trackedBuffer.h"

int getServer(const char** argv, TrackedBuffer* configLoc);
int setServer(int argc, const char** argv, TrackedBuffer* configLoc);
int signUp(int argc, const char** argv, TrackedBuffer* configLoc);
int logIn(int argc, const char** argv, TrackedBuffer* configLoc);