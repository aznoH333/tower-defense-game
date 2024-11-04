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
    this->texture = LoadRenderTexture(63, 88);

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
    drawToRenderTexture(&this->texture, cardBackdrop, 0.0f, 0.0f, FLIP_NONE, 1.0f, WHITE);

    // draw art
    drawToRenderTexture(&this->texture, this->card->artwork, 5.0, 11.0, FLIP_NONE, 1.0f, WHITE);

    // draw name
    FontDrawToTexture(&this->texture, 5, 4, 20.0f, "%s", this->card->name);

    // draw text
    //FontDrawToTexture(&this->texture, 8, 54, 20.0f, "%s", this->card->text);

    EndTextureMode();
}


void CardInstanceDispose(CardInstance* this){
    UnloadRenderTexture(this->texture);
    free(this);
}