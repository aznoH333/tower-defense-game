#ifndef DECK
#define DECK 

#include "gcollections.h"

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