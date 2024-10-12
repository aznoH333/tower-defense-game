#include "ggamestate.h"
#include "gcollections.h"
#include <stdlib.h>


//================================================
// Variables
//================================================
Vector* states;
unsigned char currentGamestate = 0;
Gamestate* currentStatePointer = 0;

//================================================
// Setup and teardown
//================================================
void initGGamestate(){
    states = VectorInit();
}


void disposeGGamestate(){
    currentStatePointer->StateUnload();
    VectorFree(states);
}


//================================================
// Register
//================================================
void registerGamestate(Gamestate* newState){
    VectorPush(states, newState);

    if (states->elementCount == 1){
        currentStatePointer = newState;
        currentStatePointer->StateLoad();
    }
}


Gamestate* GamestateInit(void (*StateLoad)(), void (*StateUnload)(), void (*StateUpdate)()){
    Gamestate* output = malloc(sizeof(Gamestate*));

    output->StateLoad = StateLoad;
    output->StateUnload = StateUnload;
    output->StateUpdate = StateUpdate;

    return output;
}


//================================================
// Switch state
//================================================
void switchGamestate(unsigned char gamestateIndex){
    currentStatePointer->StateUnload();
    currentGamestate = gamestateIndex;
    currentStatePointer = VectorGet(states, gamestateIndex);
    currentStatePointer->StateLoad();
}


//================================================
// Update gamestate
//================================================
void updateGGamestate(){
    currentStatePointer->StateUpdate();
}

