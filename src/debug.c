/* Disasembler - spits out a textual listing of the instructions given a blob 
    of maching code.
    In this case we give it a Chunk and it will print out all
    the instructions in it.
*/
#include <stdint.h>
#include <stdio.h>

#include "debug.h"
#include "chunk.h"

// Disassemble a whole chunk going through each instruction.
void disassembleChunk(Chunk* chunk, const char *name) {
    printf("== %s ==\n", name);
    /* Let disassembleInstruction() increment the offset instead 
        of doing it in the for() loop. This is because the some 
        instructions have different sizes
    */
    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

/* Disassemble a single instruction. 
    1) Print the byte offset of the instruction. This is telling us
        where in the chunk the instruction is.
    2) Read a single byte from the bytecode at that offset. This is our 
        opCode
*/
int disassembleInstruction(Chunk *chunk, int offset) {
    printf("%04d ", offset);

    uint8_t instruction = chunk->code[offset];

    switch (instruction) {
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}
