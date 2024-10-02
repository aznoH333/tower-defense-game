#ifndef G_VECTOR
#define G_VECTOR

#include <stdbool.h>

// vector
struct Vector{
    void** elements; 
    int elementCount;
    int allocatedSize;
};
typedef struct Vector Vector;


Vector* VectorInit();
void VectorResize(Vector* v);
void VectorPush(Vector* v, void* element);
void* VectorGet(Vector* v, int index);
void VectorClear(Vector* v);
void VectorFree(Vector* v);
void VectorCombine(Vector* this, Vector* other);
void VectorClearM(Vector* v, bool keepMemory);
void VectorFreeM(Vector* v, bool keepMemory);
int VectorFindStr(Vector* v, const char* str);


#endif