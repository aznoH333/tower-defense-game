#include "enemy.h"
#include "entities.h"
#include "g3d.h"
#include "level.h"
#include "path.h"
#include <math.h>
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
    Entity* output = EntityInit((Vector3){0.0f, 0.0f, 0.0f}, &EnemyUpdate, &EnemyCollide, &EnemyDestroy, &EnemyClean, ENTITY_TYPE_ENEMY);

    Enemy* enemyData = EnemyDataInit(pathProgress, pathIndex, health, movementSpeed);

    output->extraDataIndex = EntitiesAllocateExtraData(enemyData);

    return output;
}


//================================================
// Update
//================================================
void EnemyUpdate(Entity* this){
    Enemy* extraData = EntitiesGetExtraData(this->extraDataIndex);
    Path* currentPath = &(*getCurrentLevel())->paths[extraData->pathIndex];

    // update position and rotations    
    if (PathHasReachedEnd(currentPath, extraData->pathProgress)){
        this->existanceState = ENTITY_STATE_CLEAN;
    }else {
        this->position = PathResolveEnemyLocation(currentPath, extraData->pathProgress, &this->rotation);
    }
    extraData->pathProgress += extraData->movementSpeed;
    extraData->animationTimer++;   

    // die
    if (extraData->health <= 0) {
        this->existanceState = ENTITY_STATE_DEATH;
    }

    //draw
    const char* textureName;
    unsigned char animationIndex = (extraData->animationTimer >> 2) % 4;

    switch (animationIndex) {
        case 0:     textureName = "debug_entities_0001"; break;
        case 1:     textureName = "debug_entities_0002"; break;
        default:    textureName = "debug_entities_0003"; break;
    }

    // calculate rotation
    Camera* camera = getCamera();
    float cameraRotation = CameraGet2AxisRotationTowards(camera, this->position);//CameraGet2AxisRotation(camera);
    float number = cos(this->rotation) - sin(cameraRotation);
    bool flip = cos(this->rotation - cameraRotation - ROT_90)  > 0;

    drawBillboard(textureName, this->position, 1.0f, flip);
}


void EnemyCollide(Entity* this, Entity* other){

}


//================================================
// Destroy and clean
//================================================
void EnemyDestroy(Entity* this){

}


void EnemyClean(Entity* this){
    
}
