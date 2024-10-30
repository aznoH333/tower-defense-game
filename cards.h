#ifndef CARDS 
#define CARDS 

#include "level.h"


// card targeting
#define CARD_TARGET_BUILDSPOT 0
#define CARD_TARGET_GROUND 1
#define CARD_TARGET_NONE 2

union CardTarget{
    TowerSpot* towerSpot;
    Vector2* groundTarget;
};
typedef union CardTarget CardTarget;


#define CARD_RARITY_COMMON 0
#define CARD_RARITY_UNCOMMON 1
#define CARD_RARITY_RARE 2
#define CARD_RARITY_LEGENDARY 3

// card
struct Card{
    const char* name;
    unsigned int cost;
    unsigned char rarity;
    const char* text;
    const char* artwork;
    unsigned char cardTarget;
    void (*cardFunction)(struct Card* this, CardTarget target);
};
typedef struct Card Card;


// public functions
void CardsInit();
void CardsRegisterCard(const char* name, unsigned int cost, const char* artwork, unsigned char rarity, unsigned char cardTarget, const char* text, void(*cardFunction)(Card* this, CardTarget target));
Card* CardsGetCardById(int index);
void CardsDisposeCardRegistry();


#endif