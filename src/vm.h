#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"
#include <stdint.h>

#define STACK_MAX 256

typedef struct {
    Chunk* chunk;
    uint8_t* ip;     // instruction pointer (program counter or PC)
    Value stack[STACK_MAX];
    Value* stackTop;
} VM;

typedef enum 
    { INTERPRET_OK
    , INTERPRET_COMPILE_ERROR
    , INTERPRET_RUNTIME_ERROR
    } InterpretResult;

void initVM();
void freeVM();

InterpretResult interpret(Chunk* chunk);

// Stack protocol
void push(Value value);
Value pop();



#endif