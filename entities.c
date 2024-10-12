#include "entities.h"
#include "gcollections.h"


//================================================
// Variables
//================================================
Vector* entities;


//================================================
// Setup & dispose
//================================================
void initEntities(){
    entities = VectorInit();
}


void disposeEntities(){
    VectorFree(entities);
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
                break;
        }
    }


}


void addEntity(Entity* entity){
    VectorPush(entities, entity);
}