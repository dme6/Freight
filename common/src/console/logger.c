#include <stdio.h>
#include <windows.h>

enum Color {
    BLUE = 1,
    YELLOW = 6,
    RED = 4,
    WHITE = 7
};

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

void logFewArgs() {
    logError("Not enough arguments.");
}