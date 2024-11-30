/* Representing values

Constants are stored in a constant pool named ValueArray. It is 
a dynamic array. The instruction to load a constant look up the
value by index in that array.
*/
#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;

typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif