#pragma once

int writeConfigEntry(const char* loc, const char* name, const char* data);
int getConfigEntry(const char* loc, const char* name, char** out);