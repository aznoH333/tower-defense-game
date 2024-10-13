#include "tower.h"
#include "entities.h"
#include "g3d.h"
#include "gcollections.h"
#include <stdlib.h>
#include "enemy.h"
#include "towerProjectile.h"


//================================================
// Init
//================================================
Tower* TowerInitExtraData(TowerSpot* spot, unsigned char towerId){
    Tower* this = malloc(sizeof(Tower));
    this->towerId = towerId;
    this->fireCooldown = 20;
    this->fireRate = 20;
    this->damage = 10;
    this->range = 20;
    // TODO
    return this;
}


Entity* TowerInit(TowerSpot* spot, unsigned char towerId){
    Entity* output = EntityInit((Vector3){spot->x, 0.5f, spot->y}, &TowerUpdate, &TowerCollide, &TowerDestroy, &TowerClean, ENTITY_TYPE_TOWER);

    output->extraDataIndex = EntitiesAllocateExtraData(TowerInitExtraData(spot, towerId));

    return output;
}


//================================================
// Update
//================================================
bool enemySearchFunction(Entity* caller, Entity* candidate){
    return candidate->entityType == ENTITY_TYPE_ENEMY;
}


void TowerUpdate(Entity* this){
    Tower* thisData = EntitiesGetExtraData(this->extraDataIndex);


    // targeting
    Vector* possibleTargets = EntitiesFindEntities(this, &enemySearchFunction, thisData->range);

    // find target with most progress
    Entity* target = 0;
    Enemy* targetData = 0;
    for (int i = 0; i < possibleTargets->elementCount; i++){
        Entity* possibleTarget = VectorGet(possibleTargets, i);
        Enemy* possibleTargetData = EntitiesGetExtraData(possibleTarget->extraDataIndex);

        if (target == 0 || targetData->pathProgress < possibleTargetData->pathProgress){
            target = possibleTarget;
            targetData = possibleTargetData;
        }
    }

    VectorFreeM(possibleTargets, true);

    // shooting
    if (target != 0 && thisData->fireCooldown == 0){
        thisData->fireCooldown = thisData->fireRate;
        EntitiesAddEntity(ProjectileInit(this, target, 0.01f, 0.5f, 10));
    }
    thisData->fireCooldown -= thisData->fireCooldown > 0;


    // drawing
    drawBillboard("debug_entities_0005", this->position, 1.0f, false);
}


void TowerCollide(Entity* this, Entity* other){

}


//================================================
// Destroy and clean
//================================================
void TowerDestroy(Entity* this){

}


void TowerClean(Entity* this){

}


