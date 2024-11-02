#include "gcollections.h"
#include <stdlib.h>
#include "gutil.h"




//================================================
// Vector Init and unload
//================================================
#define START_ELEMENT_COUNT 10

Vector* VectorInit(){
    Vector* out = malloc(sizeof(Vector));
    out->elements = malloc(sizeof(void*) * 10);
    out->elementCount = 0; 
    out->allocatedSize = 10;   
    return out;
}


void VectorClear(Vector* v){
    VectorClearM(v, false);
}


void VectorFree(Vector* v){
    VectorFreeM(v, false);
}


void VectorClearM(Vector* v, bool keepMemory){
    if (!keepMemory){
        for (int i = 0; i < v->elementCount; i++){
            free(v->elements[i]);
        }
    }
    
    v->elementCount = 0;
}


void VectorFreeM(Vector* v, bool keepMemory){
    VectorClearM(v, keepMemory);
    free(v->elements);
    free(v);
}


//================================================
// Vector Content manipulation
//================================================
void VectorResize(Vector* v){
    int newSize = v->allocatedSize * 10;
    v->elements = realloc(v->elements, newSize * sizeof(void*));
    if (v->elements == NULL){
        gLog(LOG_ERR, "Vector couldn't realloc");
    }
    
    v->allocatedSize = newSize;
}


void VectorPush(Vector* v, void* element){
    
    if (v->elementCount + 1 > v->allocatedSize){
        VectorResize(v);
    }
    v->elements[v->elementCount++] = element;
}


void VectorRemove(Vector* v, int index){
    if (index < 0 || index > v->elementCount){
        gLog(LOG_ERR, "Vector out of bounds access {%d}", index);
    }
    
    for (int i = index; i < v->elementCount - 1; i++){
        v->elements[i] = v->elements[i+1];
    }
    v->elementCount--;
}

void* VectorGet(Vector* v, int index){
    if (index < 0 || index > v->elementCount){
        gLog(LOG_ERR, "Vector out of bounds access {%d}", index);
    }

    return v->elements[index];
}


void VectorCombine(Vector* this, Vector* other){
    for (int i = 0; i < other->elementCount; i++){
        VectorPush(this, VectorGet(other, i));
    }
}


//================================================
// Vector Find and sort
//================================================
int VectorFindStr(Vector* v, const char* str){
    for(int i = 0; i < v->elementCount; i++){
        if (strEquals(VectorGet(v, i), str)){
            return i;
        }
    }
    return -1;
}


int VectorFind(Vector* this, void* element, bool (*comparisonFunction)(void*, void*)){
    for (int i = 0; i < this->elementCount; i++){
        if (comparisonFunction(element, VectorGet(this, i))){
            return i;
        }
    }
    return -1;
}


void VectorSortBy(Vector* v, char (*comparisonFunction)(void*, void*)){
    gLog(LOG_ERR, "sort by not implemented???");
}


//================================================
// Vector iterator
//================================================
void VectorGetIterator(){
    return 
}
void VectorIteratorNext();
void VectorIteratorHasNext();

//================================================
// Map init and dispose
//================================================
Map* MapInit(bool (*comparisonFunction)(void*, void*)){
    Map* this = malloc(sizeof(Map));

    this->keys = VectorInit();
    this->values = VectorInit();
    this->comparisonFunction = comparisonFunction;

    return this;
}


void MapFree(Map* this, bool keepMemory){
    VectorFreeM(this->keys, keepMemory);
    VectorFreeM(this->values, keepMemory);

    free(this);
}


//================================================
// Put & get
//================================================
void MapPut(Map* this, void* key, void* value){
    VectorPush(this->keys, key);
    VectorPush(this->values, value);
}


void* MapGet(Map* this, void* key){
    return VectorGet(this->values, MapFindKey(this, key));
}


int MapFindKey(Map* this, void* key){
    return VectorFind(this->keys, key, this->comparisonFunction);
}

