#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/trackedBuffer.h>

TrackedBuffer* createTrackedBuffer(size_t size) {

    TrackedBuffer* tb = malloc(sizeof(TrackedBuffer));
    tb->size = size;

    if(size < 1) {
        tb->alloc = 0;
    } else {
        tb->alloc = malloc(size);
    }

    return tb;

}

void expandTrackedBuffer(TrackedBuffer* tb, size_t expansion) {

    size_t new = tb->size + expansion;

    tb->size = new;
    tb->alloc = realloc(tb->alloc, new);

}

void resizeTrackedBuffer(TrackedBuffer* tb, size_t size) {

    tb->size = size;
    tb->alloc = realloc(tb->alloc, size);

}

void cleanTrackedBuffer(TrackedBuffer* tb) {

    free(tb->alloc);
    free(tb);

}

void clearTrackedBuffer(TrackedBuffer* tb) {

    memset(tb->alloc, 0, tb->size);

}