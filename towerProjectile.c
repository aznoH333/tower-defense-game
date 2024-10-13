#include "towerProjectile.h"
#include "entities.h"
#include "enemy.h"
#include "g3d.h"
#include "gutil.h"
#include <stdlib.h>
#include <math.h>

//================================================
// Init
//================================================
Projectile* ProjectileInitExtraData(Entity* caster, Entity* target, float progressSpeed, float arch, unsigned short damage){
    Projectile* this = malloc(sizeof(Projectile));

    this->caster = caster;
    this->target = target;
    this->progress = 0.0f;
    this->progressSpeed = progressSpeed;
    this->arch = arch;
    this->damage = damage;

    return this;
}


Entity* ProjectileInit(Entity* caster, Entity* target, float progressSpeed, float arch, unsigned short damage){
    Entity* this = EntityInit(caster->position, &ProjectileUpdate, &ProjectileCollide, &ProjectileDestroy, &ProjectileClean, ENTITY_TYPE_TOWER_PROJECTILE);

    this->extraDataIndex = EntitiesAllocateExtraData(ProjectileInitExtraData(caster, target, progressSpeed, arch, damage));

    return this;
}


//================================================
// Update
//================================================
void ResolvePosition(Entity* this, Projectile* thisData){
    float rotation = dirTowards(thisData->caster->position.x, thisData->caster->position.z, thisData->target->position.x, thisData->target->position.z);
    this->rotation = rotation;
    float distance = pythagoras(thisData->caster->position.x, thisData->caster->position.z, thisData->target->position.x, thisData->target->position.z);

    float y = lerp(thisData->caster->position.y, thisData->target->position.y, thisData->progress) + (sin(thisData->progress * PI) * thisData->arch);    

    this->position.x = thisData->caster->position.x - (sin(rotation) * thisData->progress * distance);
    this->position.z = thisData->caster->position.z - (cos(rotation) * thisData->progress * distance);
    this->position.y = y;
}


void ProjectileUpdate(Entity* this){
    Projectile* thisData = EntitiesGetExtraData(this->extraDataIndex);
    // resolve position
    thisData->progress += thisData->progressSpeed;
    ResolvePosition(this, thisData);

    if (thisData->progress > 1.0f){
        // hit target
        this->existanceState = ENTITY_STATE_DEATH;
        //thisData->target->extraDataIndex;

    }

    // draw
    drawBillboard("debug_entities_0006", this->position, 1.0f, false);
}


void ProjectileCollide(Entity* this, Entity* other){

}


//================================================
// Destroy
//================================================
void ProjectileDestroy(Entity* this){
    
}


void ProjectileClean(Entity* this){

}

