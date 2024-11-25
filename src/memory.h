#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"


/* 
Macro that calculates a new capacity based on a given
current capacity
*/
#define GROW_CAPACITY(capacity) \
    ( (capacity) < 8 ? 8        \
    : (capacity) * 2            \
    )

#define GROW_ARRAY(type, pointer, oldCount, newCount)  \
    (type*)reallocate( pointer                         \
                     , sizeof(type) * (oldCount)       \
                     , sizeof(type) * (newCount)       \
                     )

#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

/* void* is a pointer to memory that has no associated data type with it */
void* reallocate(void* pointer, size_t oldSize, size_t newSize);

#endif