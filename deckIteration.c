#include "deckIteration.h"
#include <stdlib.h>
#include "gutil.h"
#include "g3d.h"


//================================================
// Init and unload
//================================================
DeckIteration* DeckIterationInit(Deck* deck, Vector3 libraryDrawPositon, Vector3 graveyardDrawPosition){
    DeckIteration* this = malloc(sizeof(DeckIteration));

    this->deck = deck;
    this->library = VectorInit();
    this->hand = VectorInit();
    this->graveyard = VectorInit();
    this->libraryDrawPosition = libraryDrawPositon;
    this->graveyardDrawPosition = graveyardDrawPosition;

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

    VectorClearM(this->graveyard, true);

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
const Vector4 CARD_MODEL_SIZE = {1.97f,2.75f,1.0f,1.0f};
const Vector4 CARD_ARTWORK_MODEL_SIZE = {1.66f, 1.25f, 1.0f, 1.0f};
const float CARD_VERTICAL_STACK_OFFSET = 0.01f;
const float CARD_VERTICAL_ART_OFFSET = 0.001f;
const float CARD_ARTWORK_Z_OFFSET = -0.40f;


void drawCardFront(int cardId, Vector3 position, Vector3 rotation){
    Card* card = CardsGetCardById(cardId);

    // set correct card backdrop
    const char* cardBackdrop;
    switch (card->rarity) {
        case CARD_RARITY_COMMON:    cardBackdrop = "debug_cards_0002";break;
        case CARD_RARITY_UNCOMMON:  cardBackdrop = "debug_cards_0003";break;
        case CARD_RARITY_RARE:      cardBackdrop = "debug_cards_0004";break;
        case CARD_RARITY_LEGENDARY:
            gLog(LOG_ERR, "legendary quality not implemented");
    }
    
    // draw backdrop
    drawPlaneS(cardBackdrop, position, rotation, 1.0f, CARD_MODEL_SIZE);

    // draw artwork
    drawPlaneS(card->artwork, (Vector3){position.x, position.y + CARD_VERTICAL_ART_OFFSET, position.z + CARD_ARTWORK_Z_OFFSET}, rotation, 1.0f, CARD_ARTWORK_MODEL_SIZE);
}


void drawLibrary(DeckIteration* this){
    for (int i = 0; i < this->library->elementCount; i++){
        Vector3 cardPosition = this->libraryDrawPosition;
        cardPosition.y += (i + 1) * CARD_VERTICAL_STACK_OFFSET;
        drawPlaneS("debug_cards_0001", cardPosition, (Vector3){0.0f, 0.0f, 0.0f}, 1.0f, CARD_MODEL_SIZE);
    }
}


void drawYard(DeckIteration* this){
    for (int i = 0; i < this->graveyard->elementCount; i++){
        int* cardId = VectorGet(this->graveyard, i);
        Vector3 cardPosition = this->graveyardDrawPosition;
        cardPosition.y += (i + 1) * CARD_VERTICAL_STACK_OFFSET;
        drawCardFront(*cardId, cardPosition, (Vector3){0.0f, 0.0f, 0.0f});
    }
}


void DeckIterationUpdate(DeckIteration* this){
    // TODO
    drawLibrary(this);
    drawYard(this);

}