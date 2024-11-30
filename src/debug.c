/* Disasembler - spits out a textual listing of the instructions given a blob 
    of maching code.
    In this case we give it a Chunk and it will print out all
    the instructions in it.
*/
#include <stdint.h>
#include <stdio.h>

#include "debug.h"
#include "chunk.h"
#include "value.h"

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

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2;      // Return the offset of the next instruction.
                            // Here the offset is 2, one for the opCode
                            // and one for the operand.
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
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}
