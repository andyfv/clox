#ifndef clox_chunk_h
#define clox_chunk_h

#include <stdint.h>

#include "common.h" 
#include "value.h"


/* Each instruction has a one-byte operation code (opcode).
    That number controls what kind of instruction we are 
    dealing with.

    Each bytecode has an 'instruction format'. For example some
    opcodes allow instructions to have operands.These are usually
    stored immediately after the opcode in the instruction stream.
    The operands specify which constant to load from the constants 
    array.
*/
typedef enum 
    { OP_CONSTANT
    , OP_RETURN
    } OpCode;


/* Chunk is a sequence of bytecode
    Along with the instructions (opcodes) there is some
    additional data. Bytecode is a series of 
    instructions. We store the bytecode in a dynamic array because
    we don't know how big the array needs to be before
    we start compiling.

    @code     : dynamic array of bytes
    @count    : number of entries in the array actually in use
    @capacity : number of elements in the array
*/
typedef struct {
    uint8_t*   code;
    ValueArray constants;
    int        count;          // number of elements in the array 
    int        capacity;       // number of entries in use
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte);
int addConstant(Chunk* chunk, Value value);
void freeChunk(Chunk* chunk);

#endif