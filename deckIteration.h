#ifndef DECK_ITERATION
#define DECK_ITERATION 

#include "deck.h"
#include "cards.h"

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
void DeckIterationDiscardCard(DeckIteration* this, int index);
Card* DeckIterationGetCardInHand(DeckIteration* this, int index);
Vector* DeckIterationGetCardsInHand(DeckIteration* this);



#endif