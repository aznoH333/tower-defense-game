#include "towerManager.h"
#include "entities.h"
#include "level.h"
#include "tower.h"


void TowerManagerBuildTower(unsigned char towerId, TowerSpot* towerSpot){
    if (towerSpot->TOWER_SPOT_STATUS == TOWER_SPOT_EMPTY){
        addEntity(TowerInit(towerSpot, towerId));
        towerSpot->TOWER_SPOT_STATUS = TOWER_SPOT_FULL;
    }
}
