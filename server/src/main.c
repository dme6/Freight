#include <stdlib.h>
#include "args/handle.h"

int main(int argc, char** argv) {
    
    if(!handleArgs(argc, argv)) return EXIT_FAILURE;

}