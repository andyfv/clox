#include <stdio.h>

#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "value.h"
#include "vm.h"

VM vm;

static void resetStack() {
    vm.stackTop = vm.stack;
}

void initVM() {
    resetStack();
}

void freeVM() {

}

/*  Push value on the top of the stack
    (1) Store the the value in the array element at the top of the stack
    (2) Increment the pointer to point to the next unused slot in the array
*/
void push(Value value) {    
    *vm.stackTop = value;   // (1)
    vm.stackTop++;          // (2)
}

/* Pop an element from the top of the stack
    (1) Move the pointer back(--) to the most recent used slot in the array
    (2) Return the value at that index
*/
Value pop() {
    vm.stackTop--;          // (1)
    return *vm.stackTop;    // (2)
}

static InterpretResult run() {
    /*  Reads the byte currently pointed at by 'ip' */
    #define READ_BYTE() (*vm.ip++)

    /*  Reads the next byte from the bytecode and treats the number
        as an index and looks up the corresponding Value in the
        constants table 
    */
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    for (;;) {
        #ifdef DEBUG_TRACE_EXECUTION
            printf("        ");
            /*  Loop and print each value on the stack array,
                starting from the bottom of the stack.
            */
            for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
                printf("[");
                printValue(*slot);
                printf("]");
            }
            printf("\n");
            disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
        #endif

        uint8_t instruction;
        switch (instruction = READ_BYTE ()) {
            case OP_CONSTANT:
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
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