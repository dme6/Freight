#pragma once

typedef struct {

    void* alloc;
    size_t size;

} TrackedBuffer;

TrackedBuffer* createTrackedBuffer(size_t size);
void expandTrackedBuffer(TrackedBuffer* tb, size_t expansion);
void cleanTrackedBuffer(TrackedBuffer* tb);
void resizeTrackedBuffer(TrackedBuffer* tb, size_t size);
void clearTrackedBuffer(TrackedBuffer* tb);
