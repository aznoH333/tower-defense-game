#include "registry.h"
#include "entities.h"
#include "ggamestate.h"


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
