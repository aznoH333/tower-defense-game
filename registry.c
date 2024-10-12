#include "registry.h"
#include "enemy.h"
#include "entities.h"
#include "ggamestate.h"
#include <raylib.h>
#include "level.h"


//================================================
// Game states
//================================================
Level* currentLevel;


void gameLoad(){
    initEntities();
    currentLevel = generateLevel();
}


void gameUnload(){
    disposeEntities();
    LevelUnload(currentLevel);
}


void gameUpdate(){
    updateEntities();
    
    if (IsKeyPressed(KEY_M)){
        addEntity(EnemyInit(0.0f, 0, 100, 0.1f));
    }

    LevelDraw(currentLevel);
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
