#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h" 
#include <stdint.h>

/* Each instruction has a one-byte operation code (opcode).
    That number controls what kind of instruction we are 
    dealing with
*/
typedef enum {
    OP_RETURN,
} OpCode;


// Additional data along with the instructions (opcodes)
typedef struct {
    uint8_t* code;
    int count;          // number of elements in the array 
    int capacity;       // number of entries in use
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte);
void freeChunk(Chunk* chunk);

#endif