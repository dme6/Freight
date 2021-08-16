#include <stdio.h>
#include <windows.h>

#define BLUE 1
#define YELLOW 6
#define RED 4
#define WHITE 7

// printf("\x1b[34mINFO: %s\x1b[0m\n", msg);

void logInfo(const char* msg) {

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, BLUE);
    printf("INFO: %s\n", msg);
    SetConsoleTextAttribute(console, WHITE);

}

void logWarning(const char* msg) {

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, YELLOW);
    printf("WARNING: %s\n", msg);
    SetConsoleTextAttribute(console, WHITE);

}

void logError(const char* msg) {

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, RED);
    printf("ERROR: %s\n", msg);
    SetConsoleTextAttribute(console, WHITE);

}