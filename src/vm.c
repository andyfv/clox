#include <stdio.h>

#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm;

void initVM() {

}

void freeVM() {

}

static InterpretResult run() {
    /*  Reads the byte currently pointed at by 'ip' */
    #define READ_BYTE() (*vm.ip++)

    /*  Read the next byte from the bytecode and treats the number
        as an index and looks up the corresponding Value in the
        constants table 
    */
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    for (;;) {
        #ifdef DEBUG_TRACE_EXECUTION
            disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
        #endif
        
        uint8_t instruction;
        switch (instruction = READ_BYTE ()) {
            case OP_CONSTANT:
                Value constant = READ_CONSTANT();
                printValue(constant);
                printf("\n");
                break;
            case OP_RETURN: {
                return INTERPRET_OK;
            }
        }
    }

    // Undefine the function macros 
    #undef READ_BYTE
    #undef READ_CONSTANT
}

InterpretResult interpret(Chunk *chunk) {
    vm.chunk = chunk;
    vm.ip    = vm.chunk->code;
    return run(); 
}