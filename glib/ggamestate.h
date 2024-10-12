#ifndef GAME_STATE_MANAGEMENT
#define GAME_STATE_MANAGEMENT


struct Gamestate{
    void (*StateLoad)();
    void (*StateUnload)();
    void (*StateUpdate)();
};
typedef struct Gamestate Gamestate;


void initGGamestate();
void disposeGGamestate();
void registerGamestate(Gamestate* newState);
void switchGamestate(unsigned char gamestateIndex);
void updateGGamestate();
Gamestate* GamestateInit(void (*StateLoad)(), void (*StateUnload)(), void (*StateUpdate)());


#endif