#include "registry.h"
#include "enemy.h"
#include "entities.h"
#include "ggamestate.h"
#include <raylib.h>
#include "level.h"
#include "towerManager.h"
#include "cameraManager.h"


//================================================
// Game states
//================================================
void gameLoad(){
    *getCurrentLevel() = generateLevel();
    EntitiesInit();
    CameraInit();
}


void gameUnload(){
    EntitiesDispose();
    LevelUnload(*getCurrentLevel());
    CameraUnload();
}


void gameUpdate(){
    // temporary controls
    if (IsKeyPressed(KEY_M)){
        EntitiesAddEntity(EnemyInit(0.0f, 0, 100, 0.025f));
    }

    if (IsKeyPressed(KEY_L)){
        (*getCurrentLevel())++;
    }

    if (IsKeyPressed(KEY_N)){
        TowerManagerBuildTower(0, &(*getCurrentLevel())->towerSpots[0]);
    }

    // update
    EntitiesUpdate();
    LevelDraw(*getCurrentLevel());
    CameraUpdate();
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
