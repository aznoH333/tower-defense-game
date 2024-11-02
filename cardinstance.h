#ifndef CARD_INSTANCE
#define CARD_INSTANCE 


#include "raylib.h"
#include "cards.h"


#define DEFAULT_CARD_SCALE_X
#define DEFAULT_CARD_SCALE_Y
// represents in hand card
// can be affected by cost reducers ect
struct CardInstance{
    int cardIdentifier;
    Card* card;
    RenderTexture2D texture;
};
typedef struct CardInstance CardInstance;


CardInstance* CardInstanceInit(int cardId);
void CardInstanceRedrawTexture(CardInstance* this);
void CardInstanceDispose(CardInstance* this);
#endif