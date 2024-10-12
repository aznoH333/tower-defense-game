#include "enemy.h"
#include "entities.h"
#include "g3d.h"
#include <stdlib.h>


//================================================
// Init
//================================================
Enemy* EnemyDataInit(Vector3 position, unsigned char pathIndex, unsigned short health, float movementSpeed){
    Enemy* output = malloc(sizeof(Enemy));
    output->movementSpeed = movementSpeed;
    output->health = health;
    output->pathIndex = pathIndex;
}


Entity* EnemyInit(Vector3 position, unsigned char pathIndex, unsigned short health, float movementSpeed){
    Entity* output = EntityInit(position, &EnemyUpdate, &EnemyCollide, &EnemyDestroy, &EnemyClean);

    Enemy* enemyData = EnemyDataInit(position, pathIndex, health, movementSpeed);

    output->extraDataIndex = allocateExtraData(enemyData);

    return output;
}


//================================================
// Update
//================================================
void EnemyUpdate(Entity* this){
    drawBillboard("debug_entities_0001", this->position, 1.0f);
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
