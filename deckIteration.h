#ifndef DECK_ITERATION
#define DECK_ITERATION 

#include "deck.h"

struct DeckIteration{
    Deck* deck;
    Vector* hand;
    Vector* graveyard;
    Vector* library;
};
typedef struct DeckIteration DeckIteration;

DeckIteration* DeckIterationInit(Deck* deck);
void DeckIterationShufleLibrary(DeckIteration* this);
void DeckIterationReturnYardToLibrary(DeckIteration* this);
void DeckIterationDrawCard(DeckIteration* this);
void DeckIterationDispose(DeckIteration* this);
void DeckIterationUpdate(DeckIteration* this);

#endif