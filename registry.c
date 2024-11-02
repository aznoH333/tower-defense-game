#include "registry.h"
#include "cardinstance.h"
#include "cards.h"
#include "entities.h"
#include "gfont.h"
#include "ggamestate.h"
#include <raylib.h>
#include "level.h"
#include "towerManager.h"
#include "cameraManager.h"
#include "enemyWaves.h"
#include "gutil.h"
#include "deck.h"
#include "deckIteration.h"
#include "g3d.h"


//================================================
// Game states
//================================================
EnemyWaves* w;
Deck* deck;
DeckIteration* deckIteration;
int selectedCardInHand = -1;

void gameLoad(){
    *getCurrentLevel() = generateLevel();
    EntitiesInit();
    CameraInit();
    w = EnemyWavesInit();
    deck = DeckInit();
    DeckAddCard(deck, 0); // Temporary add test card
    DeckAddCard(deck, 0); // Temporary add test card
    DeckAddCard(deck, 0);
    DeckAddCard(deck, 1);


    deckIteration = DeckIterationInit(deck, (Vector3){-2.0f, 0.0f, 8.0f}, (Vector3){-4.0f, 0.0f, 8.0f});

    DeckIterationDrawCard(deckIteration); // temporary card draw
    DeckIterationDrawCard(deckIteration);

}


void gameUnload(){
    EntitiesDispose();
    LevelUnload(*getCurrentLevel());
    CameraUnload();
    EnemyWavesDispose(w);
    DeckIterationDispose(deckIteration);
    DeckDispose(deck);
}


void gameUpdate(){

    EnemyWavesUpdate(w);
    // temporary controls
    if (IsKeyPressed(KEY_M)){
        EnemyWavesStartNextWave(w);
    }

    if (IsKeyPressed(KEY_L)){
        (*getCurrentLevel())++;
    }

    if (IsKeyPressed(KEY_N)){
        TowerManagerBuildTower(0, &(*getCurrentLevel())->towerSpots[0]);
    }
    
    // temporary card select
    for (int i = KEY_ONE; i < KEY_ONE + deckIteration->hand->elementCount; i++){
        if (IsKeyPressed(i)){
            selectedCardInHand = i - KEY_ONE;
            gLog(LOG_DBG, "[hand] - Selected card [%d]", selectedCardInHand);
        }
    }

    // temporary deck update
    DeckIterationUpdate(deckIteration);

    // debug
    for (int i = 0; i < MAX_TOWER_SPOTS; i++){
        TowerSpot* t = &(*getCurrentLevel())->towerSpots[i];
        drawBoundingBox((BoundingBox){(Vector3){t->x - 0.5f, t->terrainHeightOffset - 0.5f, t->y - 0.5f}, (Vector3){t->x + 0.5f, t->terrainHeightOffset + 0.5f, t->y + 0.5f}}, RED);
    }
    
    // temporary building
    if (selectedCardInHand >= 0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        for (int i = 0; i < MAX_TOWER_SPOTS; i++){
            TowerSpot* t = &(*getCurrentLevel())->towerSpots[i];

            if (t->TOWER_SPOT_STATUS != TOWER_SPOT_EMPTY){
                continue;
            }


            RayCollision result = GetRayCollisionBox(CameraGetMouseRay(), (BoundingBox){(Vector3){t->x - 0.5f, t->terrainHeightOffset - 0.5f, t->y - 0.5f}, (Vector3){t->x + 0.5f, t->terrainHeightOffset + 0.5f, t->y + 0.5f}}); 
            if (result.hit){
                CardInstance* temporaryCard = DeckIterationGetCardInHand(deckIteration, selectedCardInHand);
                gLog(LOG_DBG, "placing tower [%s]", temporaryCard->card->name);

                temporaryCard->card->cardFunction(temporaryCard->card, (CardTarget){t});
                DeckIterationDiscardCard(deckIteration, selectedCardInHand);
                DeckIterationDrawCard(deckIteration);
                selectedCardInHand = - 1;
                break;
            }
        }
    }
    

    // update
    EntitiesUpdate();
    LevelDraw(*getCurrentLevel());
    CameraUpdate();
}


void registerGamestates(){
    registerGamestate(GamestateInit(&gameLoad, &gameUnload, &gameUpdate));
}


//================================================
// Cards
//================================================
void testCardFunction(Card* this, CardTarget target){
    TowerManagerBuildTower(0, target.towerSpot);
    gLog(LOG_DBG, "Test card effect active");
}


void registerCards(){
    CardsRegisterCard("Testovaci karticka", 100, "debug_artwork_0001", CARD_RARITY_COMMON, CARD_TARGET_BUILDSPOT, "Udelej se", &testCardFunction);   
    CardsRegisterCard("Testovaci karticka 2 ", 100, "debug_artwork_0002", CARD_RARITY_RARE, CARD_TARGET_BUILDSPOT, "Udelej se", &testCardFunction);   

}


//================================================
// Public function
//================================================
void registerContet(){
    registerCards();
    registerGamestates();
}
