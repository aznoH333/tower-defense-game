#include "enemy.h"
#include "entities.h"
#include "g3d.h"
#include "level.h"
#include "path.h"
#include <raylib.h>
#include <stdlib.h>


//================================================
// Init
//================================================
Enemy* EnemyDataInit(float pathProgress, unsigned char pathIndex, unsigned short health, float movementSpeed){
    Enemy* output = malloc(sizeof(Enemy));
    output->movementSpeed = movementSpeed;
    output->health = health;
    output->pathIndex = pathIndex;
    output->animationTimer = 0;
    return output;
}


Entity* EnemyInit(float pathProgress, unsigned char pathIndex, unsigned short health, float movementSpeed){
    Entity* output = EntityInit((Vector3){0.0f, 0.0f, 0.0f}, &EnemyUpdate, &EnemyCollide, &EnemyDestroy, &EnemyClean);

    Enemy* enemyData = EnemyDataInit(pathProgress, pathIndex, health, movementSpeed);

    output->extraDataIndex = allocateExtraData(enemyData);

    return output;
}


//================================================
// Update
//================================================
void EnemyUpdate(Entity* this){
    Enemy* extraData = getExtraData(this->extraDataIndex);
    
    if (PathHasReachedEnd(&(*getCurrentLevel())->paths[extraData->pathIndex], extraData->pathProgress)){
        this->existanceState = ENTITY_STATE_CLEAN;
    }else {
        this->position = PathResolveEnemyLocation(&(*getCurrentLevel())->paths[extraData->pathIndex], extraData->pathProgress);
    }
    extraData->pathProgress += extraData->movementSpeed;
    extraData->animationTimer++;   


    //draw
    const char* textureName;
    unsigned char animationIndex = (extraData->animationTimer >> 2) % 4;

    switch (animationIndex) {
        case 0:     textureName = "debug_entities_0001"; break;
        case 1:     textureName = "debug_entities_0002"; break;
        default:    textureName = "debug_entities_0003"; break;
    }

    drawBillboard(textureName, this->position, 1.0f);

}


void EnemyCollide(Entity* this, Entity* other){

}


//================================================
// Destroy and clean
//================================================
void EnemyDestroy(Entity* this){

}


void EnemyClean(Entity* this){
    if (this->extraDataIndex != -1){
        removeExtraData(this->extraDataIndex);
    }
}
