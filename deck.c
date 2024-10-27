#include "deck.h"
#include "gcollections.h"
#include <stdlib.h>


Deck* DeckInit(){
    Deck* this = malloc(sizeof(Deck));

    this->cards = VectorInit();

    return this;
}


void DeckAddCard(Deck* this, unsigned int cardIdentifier){
    // nemuzes vyhrat
    int* cardId = malloc(sizeof(int));
    *cardId = cardIdentifier;
    VectorPush(this->cards, cardId);   
}


void DeckRemoveCard(Deck* this, unsigned int cardIndex){
    VectorRemove(this->cards, cardIndex);
}


Vector* DeckGetCards(Deck* this){
    return this->cards;
}


void DeckDispose(Deck* this){
    VectorFree(this->cards);
}