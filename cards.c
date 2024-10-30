#include "cards.h"
#include "gcollections.h"
#include "level.h"
#include "stdlib.h"


//================================================
// Variables
//================================================
Vector* cardRegistry;


//================================================
// Init & dispose
//================================================
void CardsInit(){
    cardRegistry = VectorInit();
}


void CardsDisposeCardRegistry(){
    VectorFree(cardRegistry);
}


//================================================
// Card registery
//================================================
void CardsRegisterCard(const char* name, unsigned int cost, const char* artwork, unsigned char rarity, unsigned char cardTarget, const char* text, void(*cardFunction)(Card* this, CardTarget target)){
    Card* card = malloc(sizeof(Card));

    card->name = name;
    card->cost = cost;
    card->rarity = rarity;
    card->artwork = artwork;
    card->text = text;
    card->cardTarget = cardTarget;
    card->cardFunction = cardFunction;

    VectorPush(cardRegistry, card);
}


Card* CardsGetCardById(int index){
    return VectorGet(cardRegistry, index);
}