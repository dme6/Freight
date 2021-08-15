#pragma once

int writeConfigEntry(const char* loc, const char* name, const char* data);
int getConfigEntry(char* out, const char* loc, const char* name);