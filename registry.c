#include "registry.h"
#include "enemy.h"
#include "entities.h"
#include "ggamestate.h"
#include <raylib.h>


//================================================
// Game states
//================================================
void gameLoad(){
    initEntities();
}


void gameUnload(){
    disposeEntities();
}


void gameUpdate(){
    updateEntities();
    if (IsKeyPressed(KEY_M)){
        addEntity(EnemyInit((Vector3){0,0,0}, 0, 100, 0.1f));
    }
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
