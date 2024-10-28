#include "deckIteration.h"
#include <stdlib.h>
#include "gutil.h"


//================================================
// Init and unload
//================================================
DeckIteration* DeckIterationInit(Deck* deck){
    DeckIteration* this = malloc(sizeof(DeckIteration));

    this->deck = deck;
    this->library = VectorInit();
    this->hand = VectorInit();
    this->graveyard = VectorInit();

    // add cards from deck to library
    for (int i = 0; i < deck->cards->elementCount; i++){
        VectorPush(this->library, VectorGet(deck->cards, i));
    }

    DeckIterationShufleLibrary(this);

    return this;
}


void DeckIterationDispose(DeckIteration* this){
    VectorFreeM(this->library, true);
    VectorFreeM(this->hand, true);
    VectorFreeM(this->graveyard, true);
    free(this);
}


//================================================
// Shufling
//================================================
void DeckIterationShufleLibrary(DeckIteration* this){
    gLog(LOG_DBG, "[Deck] - Shuffled library");
    Vector* shuffledLibrary = VectorInit();

    while(this->library->elementCount > 0){
        int index = getRandomInt(this->library->elementCount - 1);
        gLog(LOG_DBG, "shuffling [%d]", index);

        int* card = VectorGet(this->library, index);

        VectorPush(shuffledLibrary, card);
        VectorRemove(this->library, index);
    }

    VectorFreeM(this->library, true);
    this->library = shuffledLibrary;
}


void DeckIterationReturnYardToLibrary(DeckIteration* this){
    gLog(LOG_DBG, "[Deck] - Returned graveyard to library");
    
    for (int i = 0; i < this->graveyard->elementCount; i++){
        VectorPush(this->library, VectorGet(this->graveyard, i));
    }

    DeckIterationShufleLibrary(this);
}


void DeckIterationDrawCard(DeckIteration* this){
    gLog(LOG_DBG, "[Deck] - Drawn a card");
    
    if (this->library->elementCount == 0){
        DeckIterationReturnYardToLibrary(this);
    }

    int* ptr = VectorGet(this->library, this->library->elementCount - 1);
    VectorPush(this->hand, ptr);
    VectorRemove(this->library, this->library->elementCount - 1);
}


void DeckIterationDiscardCard(DeckIteration* this, int index){
    gLog(LOG_DBG, "[Deck] - Discarded card");
    
    VectorPush(this->graveyard, VectorGet(this->hand, index));
    VectorRemove(this->hand, index);
}


//================================================
// Getters
//================================================
Card* DeckIterationGetCardInHand(DeckIteration* this, int index){
    return CardsGetCardById(*(int*)VectorGet(this->hand,index));
}


Vector* DeckIterationGetCardsInHand(DeckIteration* this){
    return this->hand;
}


//================================================
// Update
//================================================
void DeckIterationUpdate(DeckIteration* this){
    // TODO
}