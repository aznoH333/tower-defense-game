#ifndef TOWER 
#define TOWER 

#include "level.h"
#include "entities.h"


struct Tower{
    unsigned char towerId;
    // TODO
};
typedef struct Tower Tower;

Entity* TowerInit(TowerSpot* spot, unsigned char towerId);
void TowerUpdate(Entity* this);
void TowerCollide(Entity* this, Entity* other);
void TowerDestroy(Entity* this);
void TowerClean(Entity* this);


#endif