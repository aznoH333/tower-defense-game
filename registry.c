#include "registry.h"
#include "enemy.h"
#include "entities.h"
#include "ggamestate.h"
#include <raylib.h>
#include "level.h"
#include "towerManager.h"


//================================================
// Game states
//================================================
void gameLoad(){
    *getCurrentLevel() = generateLevel();
    EntitiesInit();
}


void gameUnload(){
    EntitiesDispose();
    LevelUnload(*getCurrentLevel());
}


void gameUpdate(){
    EntitiesUpdate();
    
    if (IsKeyPressed(KEY_M)){
        EntitiesAddEntity(EnemyInit(0.0f, 0, 100, 0.003f));
    }

    if (IsKeyPressed(KEY_L)){
        (*getCurrentLevel())++;
    }

    if (IsKeyPressed(KEY_N)){
        TowerManagerBuildTower(0, &(*getCurrentLevel())->towerSpots[0]);
    }

    LevelDraw(*getCurrentLevel());
}


void registerGamestates(){
    registerGamestate(GamestateInit(&gameLoad, &gameUnload, &gameUpdate));
}


//================================================
// Public function
//================================================
void registerContet(){
    registerGamestates();
}
