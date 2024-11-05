#include "cardinstance.h"
#include <raylib.h>
#include <stdlib.h>
#include "cards.h"
#include "gdrawing.h"
#include "gfont.h"
#include "gutil.h"


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
        case CARD_RARITY_COMMON:    cardBackdrop = "debug_cards_0002";break;
        case CARD_RARITY_UNCOMMON:  cardBackdrop = "debug_cards_0003";break;
        case CARD_RARITY_RARE:      cardBackdrop = "debug_cards_0004";break;
        case CARD_RARITY_LEGENDARY:
            gLog(LOG_ERR, "legendary quality not implemented");
    }
    
    // draw card frame
    drawToRenderTexture(&this->texture, cardBackdrop, 0.0f, 0.0f, FLIP_NONE, 2.0f, WHITE);

    // draw art
    drawToRenderTexture(&this->texture, this->card->artwork, 10.0, 22.0, FLIP_NONE, 2.0f, WHITE);

    // draw name
    FontDrawToTexture(&this->texture, 10.0f, 8.0f, 12.0f, "%s", this->card->name);

    // draw text
    FontDrawToTexture(&this->texture, 16.0f, 108.0f, 12.0f, "%s", this->card->text);

    EndTextureMode();
}


void CardInstanceDispose(CardInstance* this){
    UnloadRenderTexture(this->texture);
    free(this);
}