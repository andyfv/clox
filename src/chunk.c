#include <stdint.h>
#include <stdlib.h>

#include "chunk.h"
#include "memory.h"
#include "value.h"


// Initialize new chunk
void initChunk(Chunk* chunk) {
    chunk->count    = 0;
    chunk->capacity = 0;
    chunk->code     = NULL;
    initValueArray(&chunk->constants);
}

/* Add a new byte and grow the array of bytecode
    if there is no space left.
*/
void writeChunk(Chunk *chunk, uint8_t byte) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code     = GROW_ARRAY( uint8_t
                                    , chunk->code
                                    , oldCapacity
                                    , chunk->capacity
                                    ); 
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;
}

/* Add a new constant to the chunk. Return the index where the 
constant was appended */
int addConstant(Chunk *chunk , Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

/* Free chunk by calling FREE_ARRAY() and zero out the chunk fields
    by calling initChunk()
*/
void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);     // Zero out the fields leaving the
                                        // chunk in well-defined state
}