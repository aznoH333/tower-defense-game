#ifndef DECK
#define DECK 

#include "gcollections.h"

/*
    This structure should store player deck
    Not intended for in game use
    For in game card usage use the deckIteration struct
*/

struct Deck{
    Vector* cards;
};
typedef struct Deck Deck;


Deck* DeckInit();
void DeckAddCard(Deck* this, unsigned int cardIdentifier);
void DeckRemoveCard(Deck* this, unsigned int cardIndex);
Vector* DeckGetCards(Deck* this);
void DeckDispose(Deck* this);

#endif