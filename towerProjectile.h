#ifndef TOWER_PROJECTILE 
#define TOWER_PROJECTILE

#include "entities.h"
#include <raylib.h>

struct Projectile{
    Entity* caster;
    Entity* target;
    Vector3 destination;
    float arch;
    float progress;
    float progressSpeed;
    unsigned short damage;

}; typedef struct Projectile Projectile;

Entity* ProjectileInit(Entity* caster, Entity* target, float progressSpeed, float arch, unsigned short damage);
void ProjectileUpdate(Entity* this);
void ProjectileCollide(Entity* this, Entity* other);
void ProjectileDestroy(Entity* this);
void ProjectileClean(Entity* this);


#endif