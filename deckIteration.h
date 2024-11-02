#ifndef DECK_ITERATION
#define DECK_ITERATION 

#include "cardinstance.h"
#include "deck.h"

struct DeckIteration{
    Deck* deck;
    Vector* hand;
    Vector* graveyard;
    Vector* library;
    Vector3 libraryDrawPosition;
    Vector3 graveyardDrawPosition;
};



typedef struct DeckIteration DeckIteration;

DeckIteration* DeckIterationInit(Deck* deck, Vector3 libraryDrawPosition, Vector3 graveyardDrawPosition);
void DeckIterationShufleLibrary(DeckIteration* this);
void DeckIterationReturnYardToLibrary(DeckIteration* this);
void DeckIterationDrawCard(DeckIteration* this);
void DeckIterationDispose(DeckIteration* this);
void DeckIterationUpdate(DeckIteration* this);
void DeckIterationDiscardCard(DeckIteration* this, int index);
CardInstance* DeckIterationGetCardInHand(DeckIteration* this, int index);
Vector* DeckIterationGetCardsInHand(DeckIteration* this);



#endif