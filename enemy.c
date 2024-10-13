#include "enemy.h"
#include "entities.h"
#include "g3d.h"
#include "level.h"
#include "path.h"
#include <math.h>
#include <raylib.h>
#include <stdlib.h>
#include "gutil.h"


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
    Path* currentPath = &(*getCurrentLevel())->paths[extraData->pathIndex];

    // update position and rotations    
    if (PathHasReachedEnd(currentPath, extraData->pathProgress)){
        this->existanceState = ENTITY_STATE_CLEAN;
    }else {
        this->position = PathResolveEnemyLocation(currentPath, extraData->pathProgress, &this->rotation);
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

    // calculate rotation
    Camera* camera = getCamera();
    float cameraRotation = CameraGet2AxisRotationTowards(camera, this->position);//CameraGet2AxisRotation(camera);
    float number = cos(this->rotation) - sin(cameraRotation);
    bool flip = cos(this->rotation - cameraRotation - ROT_90)  > 0;

    drawBillboard(textureName, this->position, 1.0f, flip);
    drawBillboard("debug_entities_0006", (Vector3){this->position.x + cos(cameraRotation), this->position.y, this->position.z + sin(cameraRotation)}, 1.0f, false);
    //drawBillboard("debug_entities_0006", (Vector3){this->position.x + cos(number), this->position.y, this->position.z + sin(number)}, 1.0f, false);

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
