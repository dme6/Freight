#pragma once

#include "../util/trackedBuffer.h"

int writeConfigEntry(TrackedBuffer* loc, const char* name, const char* data);
int getConfigEntry(TrackedBuffer* loc, const char* name, char** out);