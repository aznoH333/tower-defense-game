#include "cardinstance.h"
#include <raylib.h>
#include <stdlib.h>
#include "cards.h"
#include "gdrawing.h"
#include "gfont.h"


CardInstance* CardInstanceInit(int cardId){
    CardInstance* this = malloc(sizeof(CardInstance));
    this->card = CardsGetCardById(cardId);

    this->cardIdentifier = cardId;
    // correct resolution (disabled for testing purposes)
    //this->texture = LoadRenderTexture(63, 88);

    // scaled up resolution
    this->texture = LoadRenderTexture(126, 176);

    CardInstanceRedrawTexture(this);

    return this;
}


void CardInstanceRedrawTexture(CardInstance* this){
    BeginTextureMode(this->texture);

    // pick backdrop
    
    const char* cardBackdrop;
    switch (this->card->rarity) {
        case CARD_RARITY_COMMON:    cardBackdrop = "card_background_0002";break;
        case CARD_RARITY_UNCOMMON:  cardBackdrop = "card_background_0003";break;
        case CARD_RARITY_RARE:      cardBackdrop = "card_background_0004";break;
        case CARD_RARITY_LEGENDARY: cardBackdrop = "card_background_0005";break;
    }
    
    // draw card frame
    drawToRenderTexture(&this->texture, cardBackdrop, 0.0f, 0.0f, FLIP_NONE, 1.0f, WHITE);

    // draw art
    drawToRenderTexture(&this->texture, this->card->artwork, 11.0, 25.0, FLIP_NONE, 1.0f, WHITE);

    // draw name
    FontDrawToTexture(&this->texture, 6.0f, 6.0f, 13.0f, "%s", this->card->name);

    // draw text
    FontDrawToTexture(&this->texture, 10.0f, 104.0f, 13.0f, "%s", this->card->text);

    EndTextureMode();
}


void CardInstanceDispose(CardInstance* this){
    UnloadRenderTexture(this->texture);
    free(this);
}