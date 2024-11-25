#include "stdlib.h"

#include "memory.h"


/* Deals with all dunamic memory management:
    - allocating memory
    - freeing it
    - changing the size of existing allocation

    Based on the size arguments we perform the following operations:
    -------------------------------------------------
     oldSize |  newSize  | Operation
    ---------|-----------|---------------------------
     0       | non-zero  | allocate new block
    ---------|-----------|---------------------------
    non-zero |  0        | free allocation
    ---------|-----------|---------------------------
    non-zero | < oldSize | shrink existing allocation
    ---------|-----------|---------------------------
    non-zero | > oldSize | grow   existing allocation
    -------------------------------------------------
*/
void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }

    void* result = realloc(pointer,newSize);
    if (result == NULL) exit(1);
    return result;
}