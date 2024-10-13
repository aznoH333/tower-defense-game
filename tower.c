#include "tower.h"
#include "entities.h"
#include "g3d.h"
#include <stdlib.h>


//================================================
// Init
//================================================
Tower* TowerInitExtraData(TowerSpot* spot, unsigned char towerId){
    Tower* this = malloc(sizeof(Tower));
    this->towerId = towerId;
    // TODO
}


Entity* TowerInit(TowerSpot* spot, unsigned char towerId){
    Entity* output = EntityInit((Vector3){spot->x, 0.5f, spot->y}, &TowerUpdate, &TowerCollide, &TowerDestroy, &TowerClean);

    allocateExtraData(TowerInitExtraData(spot, towerId));

    return output;
}


//================================================
// Update
//================================================
void TowerUpdate(Entity* this){
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


