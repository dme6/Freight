#include <stdio.h>
#include <windows.h>

static const WORD BLUE   = FOREGROUND_BLUE,
                  YELLOW = FOREGROUND_BLUE | FOREGROUND_GREEN,
                  RED    = FOREGROUND_RED,
                  WHITE  = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

void logInfo(const char* msg) {

    HANDLE console = GetStdHandle(STD_ERROR_HANDLE);
    SetConsoleTextAttribute(console, BLUE);
    fprintf(stderr, "[INFO] %s\n", msg);
    SetConsoleTextAttribute(console, WHITE);

}

void logWarning(const char* msg) {

    HANDLE console = GetStdHandle(STD_ERROR_HANDLE);
    SetConsoleTextAttribute(console, YELLOW);
    fprintf(stderr, "[WARNING] %s\n", msg);
    SetConsoleTextAttribute(console, WHITE);

}

void logError(const char* msg) {

    HANDLE console = GetStdHandle(STD_ERROR_HANDLE);
    SetConsoleTextAttribute(console, RED);
    fprintf(stderr, "[ERROR] %s\n", msg);
    SetConsoleTextAttribute(console, WHITE);

}

void logFewArgs() {
    logError("Not enough arguments.");
}