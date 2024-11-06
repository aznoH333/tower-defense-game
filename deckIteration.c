#include "deckIteration.h"
#include "cameraManager.h"
#include "cardinstance.h"
#include <raylib.h>
#include <stdlib.h>
#include "gcollections.h"
#include "gfont.h"
#include "gframework.h"
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
        VectorPush(this->library, CardInstanceInit(*(int*)VectorGet(deck->cards, i)));
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

        CardInstance* card = VectorGet(this->library, index);

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

    CardInstance* ptr = VectorGet(this->library, this->library->elementCount - 1);
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
CardInstance* DeckIterationGetCardInHand(DeckIteration* this, int index){
    return ((CardInstance*)VectorGet(this->hand,index));
}


Vector* DeckIterationGetCardsInHand(DeckIteration* this){
    return this->hand;
}


//================================================
// Update
//================================================
const float CARD_VERTICAL_STACK_OFFSET = 0.05f;
const Vector4 CARD_MODEL_SIZE = {1.97f,2.75f,1.0f,1.0f};


void drawCardFront(CardInstance* card, Vector3 position, Vector3 rotation){
    drawPlaneST(&card->texture, position, rotation, 1.0f, CARD_MODEL_SIZE);
}


void drawLibrary(DeckIteration* this){
    for (int i = 0; i < this->library->elementCount; i++){
        Vector3 cardPosition = this->libraryDrawPosition;
        cardPosition.y += (i + 1) * CARD_VERTICAL_STACK_OFFSET;
        drawPlaneS("card_background_0001", cardPosition, (Vector3){0.0f, 0.0f, 0.0f}, 1.0f, CARD_MODEL_SIZE);
    }
}


void drawYard(DeckIteration* this){
    for(int i = 0; i < this->graveyard->elementCount; i++){
        CardInstance* card = VectorGet(this->graveyard, i);
        Vector3 cardPosition = this->graveyardDrawPosition;
        cardPosition.y += (i + 1) * CARD_VERTICAL_STACK_OFFSET;
        drawCardFront(card, cardPosition, (Vector3){0.0f, 0.0f, 0.0f});
    }
}

#define MIN_SPACE_BETWEEN_CARDS_IN_HAND 0.25f
#define SCALING_CARD_SPACE_OFFSET 1.75f
#define DEFAULT_CARD_DISTANCE 0.5f
#define CARD_SCALING_MULTIPLIER 0.25f
void drawHand(DeckIteration* this){
    // animation calculation
    float mouseY = GetMouseY();
    float mouseX = GetMouseX();

    float mouseDistanceFactor = lerp(0, 1,(mouseY / SCREEN_HEIGHT));
    
    float cardSpacing = MIN_SPACE_BETWEEN_CARDS_IN_HAND + (mouseDistanceFactor * SCALING_CARD_SPACE_OFFSET);
    float cardDistance = 1.0f / (DEFAULT_CARD_DISTANCE + (mouseDistanceFactor * CARD_SCALING_MULTIPLIER)); 

    // hand positioning
    Vector3 handPos = CameraGetPosition();
    handPos.y -= 4.75f + cardDistance;
    handPos.z -= 6.75f - cardDistance;

    // drawing
    float oddHandSizeOffset = ((this->hand->elementCount % 1 == 0) * 0.25f) + 0.25f;
    for (int i = 0; i < this->hand->elementCount; i++){
        CardInstance* instance = VectorGet(this->hand, i);
        float positionMultiplier = i + oddHandSizeOffset;
        float xOffset = handPos.x + (positionMultiplier * cardSpacing) - ((this->hand->elementCount * 0.5f * cardSpacing));

        drawCardFront(instance, (Vector3){xOffset, handPos.y, handPos.z}, (Vector3){30.0f,0.0f, 0.0f});
    }
}


void DeckIterationUpdate(DeckIteration* this){
    FontDraw2D(10.0f, 20.0f, 20.0f, "Cards in library : %d", this->library->elementCount);
    FontDraw2D(10.0f, 60.0f, 20.0f, "Cards in graveyard : %d", this->graveyard->elementCount);

    
    // TODO
    drawLibrary(this);
    drawYard(this);
    drawHand(this);
}