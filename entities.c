#include "entities.h"
#include "gcollections.h"
#include <stdlib.h>


//================================================
// Variables
//================================================
Vector* entities;
Vector* extraData;


//================================================
// Setup & dispose
//================================================
void initEntities(){
    entities = VectorInit();
    extraData = VectorInit();
}


void disposeEntities(){
    VectorFree(entities);
    VectorFree(extraData);
}


//================================================
// Update
//================================================
void updateEntities(){
    
    for (int i = 0; i < entities->elementCount; i++){
        Entity* entity = VectorGet(entities, i);

        // update
        entity->EntityUpdate(entity);

        switch (entity->existanceState) {
            case ENTITY_STATE_DEATH:
                entity->EntityDestroy(entity);
            case ENTITY_STATE_CLEAN:
                entity->EntityRemove(entity);
                VectorRemove(entities, i);
                i--;
                break;
        }
    }


}


//================================================
// Entity
//================================================
void addEntity(Entity* entity){
    VectorPush(entities, entity);
}


Entity* EntityInit(Vector3 position,    void (*EntityUpdate)(Entity* this), 
                                        void (*EntityCollide)(Entity* this, Entity* other), 
                                        void (*EntityDestroy)(Entity* this), 
                                        void (*EntityRemove)(Entity* this)){
    Entity* output = malloc(sizeof(Entity));

    output->position = position;
    output->EntityUpdate = EntityUpdate;
    output->EntityCollide = EntityCollide;
    output->EntityRemove = EntityRemove;
    output->extraDataIndex = -1;

    return output;
}


//================================================
// Extra data
//================================================
int allocateExtraData(void* data){
    VectorPush(extraData, data);
    return extraData->elementCount - 1;
}


void* getExtraData(int index){
    return VectorGet(extraData, index);
}


void removeExtraData(int index){
    VectorRemove(extraData, index);
    
    // decrement all extra indicies
    for (int i = 0; i < entities->elementCount; i++){
        Entity* entity = VectorGet(entities, i);

        if (entity->extraDataIndex > index){
            entity->extraDataIndex--;
        }
    }
}

