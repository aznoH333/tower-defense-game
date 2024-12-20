#include "entities.h"
#include "gcollections.h"
#include "gutil.h"
#include <raylib.h>
#include <stdlib.h>


//================================================
// Variables
//================================================
Vector* entities;
Vector* extraData;


//================================================
// Setup & dispose
//================================================
void EntitiesInit(){
    entities = VectorInit();
    extraData = VectorInit();
}


void EntitiesDispose(){
    VectorFree(entities);
    VectorFree(extraData);
}


//================================================
// Update
//================================================
void EntitiesUpdate(){
    
    for (int i = 0; i < entities->elementCount; i++){
        Entity* entity = VectorGet(entities, i);

        // update
        entity->EntityUpdate(entity);


        // collisions
        for (int j = 0; j < entities->elementCount; j++){
            if (i == j){
                continue;
            }
            Entity* other = VectorGet(entities, j);

            if (checkBoundingBoxCollisions(entity->position, entity->boundingBox, other->position, other->boundingBox)){
                entity->EntityCollide(entity, other);
            }
        }


        // destroying
        switch (entity->existanceState) {
            case ENTITY_STATE_DEATH:
                entity->EntityDestroy(entity);
            case ENTITY_STATE_CLEAN:
                entity->EntityRemove(entity);
                int dataIndex = entity->extraDataIndex;
                free(entity);
                VectorRemove(entities, i);
                
                if (dataIndex != -1){
                    EntitiesRemoveExtraData(dataIndex);
                }
                
                i--;
                break;
        }
    }


}


//================================================
// Entity
//================================================
void EntitiesAddEntity(Entity* entity){
    VectorPush(entities, entity);
}


Entity* EntityInit(Vector3 position, Vector3 boundingBox,
                                        void (*EntityUpdate)(Entity* this), 
                                        void (*EntityCollide)(Entity* this, Entity* other), 
                                        void (*EntityDestroy)(Entity* this), 
                                        void (*EntityRemove)(Entity* this),
                    char entityType){
    Entity* output = malloc(sizeof(Entity));

    output->position = position;
    output->EntityUpdate = EntityUpdate;
    output->EntityCollide = EntityCollide;
    output->EntityDestroy = EntityDestroy;
    output->EntityRemove = EntityRemove;
    output->extraDataIndex = -1;
    output->entityType = entityType;
    output->boundingBox = boundingBox;
    output->existanceState = ENTITY_STATE_ALIVE;

    return output;
}


Vector* EntitiesFindEntities(Entity* caller, bool (*validityFunction)(Entity* caller, Entity* candidate), float range){
    Vector* output = VectorInit();
    for (int i = 0; i < entities->elementCount; i++){
        Entity* entity = VectorGet(entities, i);
        if (entity != caller && distanceBetweenPoints(caller->position, entity->position) < range && validityFunction(caller, entity)){
            VectorPush(output, entity);
        }
    }
    return output;
}


//================================================
// Extra data
//================================================
int EntitiesAllocateExtraData(void* data){
    VectorPush(extraData, data);
    return extraData->elementCount - 1;
}


void* EntitiesGetExtraData(int index){
    return VectorGet(extraData, index);
}


void EntitiesRemoveExtraData(int index){
    // decrement all extra indicies
    for (int i = 0; i < entities->elementCount; i++){
        Entity* entity = VectorGet(entities, i);

        if (entity->extraDataIndex > index){
            entity->extraDataIndex--;
        }
    }
    // free element
    free(VectorGet(extraData, index));
    VectorRemove(extraData, index);
 
}

