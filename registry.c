#include "registry.h"
#include "enemy.h"
#include "entities.h"
#include "ggamestate.h"
#include <raylib.h>
#include "level.h"


//================================================
// Game states
//================================================
void gameLoad(){
    *getCurrentLevel() = generateLevel();
    initEntities();
}


void gameUnload(){
    disposeEntities();
    LevelUnload(*getCurrentLevel());
}


void gameUpdate(){
    updateEntities();
    
    if (IsKeyPressed(KEY_M)){
        addEntity(EnemyInit(0.0f, 0, 100, 0.03f));
    }

    if (IsKeyPressed(KEY_L)){
        (*getCurrentLevel())++;
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
