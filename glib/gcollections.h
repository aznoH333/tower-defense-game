#ifndef G_VECTOR
#define G_VECTOR


// vector
struct Vector{
    void** elements; 
    int elementCount;
    int allocatedSize;
};
typedef struct Vector Vector;


Vector* VectorInit();
void vectorResize(Vector* v);
void vectorPush(Vector* v, void* element);
void* VectorGet(Vector* v, int index);
void VectorClear(Vector* v);
void VectorFree(Vector* v);



#endif