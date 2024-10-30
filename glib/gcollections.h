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
int VectorFind(Vector* v, void* element, bool (*comparisonFunction)(void*, void*));
void VectorSortBy(Vector* v, char (*comparisonFunction)(void*, void*));
void VectorRemove(Vector* v, int index);

// map
struct Map{
    Vector* values;
    Vector* keys;
    bool (*comparisonFunction)(void*, void*);
};
typedef struct Map Map;


Map* MapInit(bool (*comparisonFunction)(void*, void*));
void MapPut(Map* this, void* key, void* value);
void* MapGet(Map* this, void* key);
int MapFindKey(Map* this, void* key);
void MapFree(Map* this, bool keepMemory);



#endif